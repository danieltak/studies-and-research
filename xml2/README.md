<!-- vscode-markdown-toc -->
* 1. [Introduction](#Introduction)
* 2. [SAX vs DOM vs pull parser](#SAXvsDOMvspullparser)
		* 2.1. [DOM](#DOM)
		* 2.2. [SAX](#SAX)
* 3. [Free xml Objects](#FreexmlObjects)
* 4. [xmlParser vs xmlReader](#xmlParservsxmlReader)
* 5. [Casting xmlChar](#CastingxmlChar)
* 6. [Read from file](#Readfromfile)
* 7. [Read from Memory](#ReadfromMemory)
* 8. [Write to File](#WritetoFile)
* 9. [Write to Memory](#WritetoMemory)
* 10. [Read SVG](#ReadSVG)
* 11. [Get the Attribute](#GettheAttribute)
* 12. [Check file changed](#Checkfilechanged)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

##  1. <a name='Introduction'></a>Introduction

[Libxml2](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/general.html) is the XML C parser and toolkit developed for the Gnome project.

[Libxml2](https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home) is known to be very portable, the library should build and work without serious troubles on a variety of systems (Linux, Unix, Windows, CygWin, MacOS, RISC Os, OS/2, VMS, QNX, MVS, ...).

Tutorials can be found on:
- http://www.xmlsoft.org/examples/
- https://gnome.pages.gitlab.gnome.org/libxml2/tutorial/
- https://gnome.pages.gitlab.gnome.org/libxml2/examples/

The repository:
- https://github.com/GNOME/libxml2

Read-only mirror:
- https://gitlab.gnome.org/GNOME/libxml2

##  2. <a name='SAXvsDOMvspullparser'></a>SAX vs DOM vs pull parser


https://stackoverflow.com/questions/5808105/sax-parser-vs-xmlpull-parser

>TL;DR; Use a DOM or pull parser with smaller files that fit in RAM. Use a SAX parser for large files that won't. 
>
>It totally depends on the situation for e.g If the xml file is really large than you can't opt for DOM parsers as they will first bring the file in to memory and then it will be parsed and i found that parsing a file of size n requires 7n memory space. In this case you should opt for SAX parser its light and will consume less memory.
>
>Second case is when the file is not really large, in this case you can go for XML pull parser because in this you will have full control on the xml you can skip the parsing cycle any where that is not possible in SAX. So if the tag you are looking for is the first one in the file then why would you go for whole file.
>
>So as far as i know if you consider only speed with small file go with XML pull parser and If the file is large and you want to parse it all then go with SAX.

https://stackoverflow.com/questions/6828703/what-is-the-difference-between-sax-and-dom
> In SAX, events are triggered when the XML is being parsed. When the parser is parsing the XML, and encounters a tag starting (e.g. `<something>`), then it triggers the tagStarted event (actual name of event might differ). Similarly when the end of the tag is met while parsing (`</something>`), it triggers tagEnded. Using a SAX parser implies you need to handle these events and make sense of the data returned with each event.
> 
>In DOM, there are no events triggered while parsing. The entire XML is parsed and a DOM tree (of the nodes in the XML) is generated and returned. Once parsed, the user can navigate the tree to access the various data previously embedded in the various nodes in the XML.
>
>In general, DOM is easier to use but has an overhead of parsing the entire XML before you can start using it.


>SAX (Simple API for XML): Is a stream-based processor. You only have a tiny part in memory at any time and you "sniff" the XML stream by implementing callback code for events like tagStarted() etc. It uses almost no memory, but you can't do "DOM" stuff, like use xpath or traverse trees.

>DOM (Document Object Model): You load the whole thing into memory - it's a massive memory hog. You can blow memory with even medium sized documents. But you can use xpath and traverse the tree etc.

####  2.1. <a name='DOM'></a>DOM

- Tree model parser (Object based) (Tree of nodes).
- DOM loads the file into the memory and then parse- the file.
- Has memory constraints since it loads the whole XML file before parsing.
- DOM is read and write (can insert or delete nodes).
- If the XML content is small, then prefer DOM parser.
- Backward and forward search is possible for searching the tags and evaluation of the information inside the tags. So this gives the ease of navigation.
- Slower at run time.

####  2.2. <a name='SAX'></a>SAX

- Event based parser (Sequence of events).
- SAX parses the file as it reads it, i.e. parses node by node.
- No memory constraints as it does not store the XML content in the memory.
- SAX is read only i.e. can’t insert or delete the node.
- Use SAX parser when memory content is large.
- SAX reads the XML file from top to bottom and backward navigation is not possible.
- Faster at run time.

https://stackoverflow.com/questions/11297273/difference-among-xml-sax-parser-pull-parser-dom-parser-in-android

>Dom Parser - It uses object based approach. i.e., it first loads the entire XML in memory, converts the XML nodes into objects and then starts parsing them. So, it is pretty slower.
>
>SAX and PULL Parser - they use event based approach. Both are almost same in terms of memory and performance. However there are few distinguishing situations on when to use them as described below.
>
>Dom Parser - Use it when you need to validate the entire XML before parsing. Never use it when the XML is too large and validation can be compromised. Once it starts parsing, it parses from starting node to ending node. there is no way to parse only particular nodes.
>
>SAX - Use it when you want to parse the entire XML. Once it starts parsing, it parses from starting node to ending node. there is no way to parse only particular nodes.
>
>PULL - Use it when you don't want to parse the entire XML. It is easier to implement than SAX, because you don't have to maintain the state of your parser. You can pull only a particular node you are interested at.
>
>My suggestion is - Need validation - Go for DOM, File size is small or you are not interested in parsing of entire XML- Go for PULL, File size is large or you need to parse the entire XML file - Go for SAX.
##  3. <a name='FreexmlObjects'></a>Free xml Objects

Don't forget to free the xml objects buffer and doc, mainly when the object is a class member.

Use the functions providaded by the library, such as:
- xmlFreeDoc
- xmlFreeParserCtxt
- xmlXPathFreeObject 
- xmlXPathFreeContext 
- xmlFreeTextReader 
- xmlFreeTextWriter 
- xmlBufferFree 

##  4. <a name='xmlParservsxmlReader'></a>xmlParser vs xmlReader

Although the [official tutorial](https://gnome.pages.gitlab.gnome.org/libxml2/tutorial/index.html) suggests the use of the function xmlParseFile(), it isn't recommended, use xmlReader instead. It is more powerful, [answers on Stack Overflow](https://stackoverflow.com/questions/19315206/xmlparsefile-vs-xmlreadfile-libxml2) also suggest the use of the function.

The [official documentation](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-parser.html#xmlParseFile) states that xmlParseFile is deprecated and recommends the use of [xmlReadFile](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-parser.html#xmlReadFile) instead.

However, the newer [xmlReader](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-xmlreader.html) is a better choice, even though there are lots old tutorials using xmlParseFile. Mainly when [used to parse big files](https://stackoverflow.com/a/23403898/7690982).


##  5. <a name='CastingxmlChar'></a>Casting xmlChar

According to the [documentation](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-xmlstring.html#xmlChar) a `xmlChar` is a typedef of `unsigned char`. The following description can be seen:

>This is a basic byte in an UTF-8 encoded string. It's unsigned allowing to pinpoint case where char * are assigned to xmlChar * (possibly making serialization back impossible).

There is a `BAD_CAST` macro defined:

>Macro to cast a string to an xmlChar * when one know its safe.

So a string literal can be used to declare a xmlChar using the BAD_CAST macro:

`const xmlChar* languageNode = BAD_CAST "language";`

##  6. <a name='Readfromfile'></a>Read from file

If the file is small, the deprecated `xmlParseFile` can be used:

```cpp
std::string fileName = "path/to/file.xml";
xmlDocPtr docPtr = nullptr;

docPtr = xmlParseFile( filename.c_str() );

if (docPtr == NULL)
	{
    	fprintf( stderr, "Failed to parse %s\n", filename.c_str() );
		return;
    }
xmlFreeDoc(docPtr);
```


Otherwise, `xmlReadFile` can be used:

>DEPRECATED: Use xmlReadFile. parse an XML file and build a tree. Automatic support for ZLIB/Compress compressed document is provided by default if found at compile-time.

```cpp
std::string fileName = "path/to/file.xml";
xmlDocPtr docPtr = nullptr;

docPtr = xmlReadFile(filename.c_str(), NULL, 0);

if (docPtr == NULL)
	{
    	fprintf( stderr, "Failed to parse %s\n", filename.c_str() );
		return;
    }
xmlFreeDoc(docPtr);
```

##  7. <a name='ReadfromMemory'></a>Read from Memory

`xmlParseMemory` can be used to read from memory for small buffer sizes.

>DEPRECATED: Use xmlReadMemory. parse an XML in-memory block and build a tree.

```cpp
const char *pMemory = "<?xml version='1.0'?>\n\
<document xmlns:xi=\"http://www.w3.org/2003/XInclude\">\n\
  <p>List of people:</p>\n\
  <xi:include href=\"sql:select_name_from_people\"/>\n\
</document>\n";

xmlDocPtr docPtr = nullptr;

docPtr = xmlParseMemory(pMemory, strlen(pMemory));

if (docPtr == NULL)
	{
    	fprintf( stderr, "Failed to parse %s\n", pMemory );
		return;
    }
xmlFreeDoc(docPtr);
```

Using `xmlReadMemory` instead of deprecated function:

```cpp
xmlDocPtr docPtr = nullptr;

docPtr =  xmlReadMemory(pMemory, strlen(pMemory), "pMemory.xml", NULL, 0);

if (docPtr == NULL)
	{
    	fprintf( stderr, "Failed to parse %s\n", pMemory );
		return;
    }
xmlFreeDoc(docPtr);
```

##  8. <a name='WritetoFile'></a>Write to File

`xmlNewTextWriterFilename` can be used to write to the file, some writer functions from `xmlwriter` takes `xmlTextWriterPtr` as argument to create the content of the xml.

After creating the content, end the document and free the object.

```cpp
int rc;
std::string str("/path/to/filename.xml");
xmlTextWriterPtr writer = xmlNewTextWriterFilename(str.c_str(), 0);

rc = xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
if(rc < 0)
{
	std::cout << "An error occurred on xmlTextWriterStartDocument." << std::endl;
}

rc = xmlTextWriterStartElement(writer, BAD_CAST "document");
rc = xmlTextWriterWriteAttribute(writer,
									BAD_CAST "xmlns:xi",
									BAD_CAST "http://www.w3.org/2003/XInclude" );

rc = xmlTextWriterWriteFormatComment(writer,
			"This is a comment" );

rc = xmlTextWriterEndElement(writer);

rc = xmlTextWriterWriteString(writer, BAD_CAST "List of people:");

rc = xmlTextWriterEndDocument(writer);

xmlFreeTextWriter(writer);
```

##  9. <a name='WritetoMemory'></a>Write to Memory

`xmlNewTextWriterMemory` can be used to write to the buffer memory, some writer functions from `xmlwriter` takes `xmlTextWriterPtr` as argument to create the content of the xml.

After creating the content, end the document and free the objects (writer and buffer).

```cpp
xmlBufferPtr buffer = xmlBufferCreate();
xmlTextWriterPtr writer = xmlNewTextWriterMemory(buffer, 0);

rc = xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
if(rc < 0)
{
	std::cout << "An error occurred on xmlTextWriterStartDocument." << std::endl;
}

rc = xmlTextWriterStartElement(writer, BAD_CAST "document");
rc = xmlTextWriterWriteAttribute(writer,
									BAD_CAST "xmlns:xi",
									BAD_CAST "http://www.w3.org/2003/XInclude" );

rc = xmlTextWriterWriteFormatComment(writer,
			"This is a comment" );
rc = xmlTextWriterEndElement(writer);

rc = xmlTextWriterWriteString(writer, BAD_CAST "List of people:");

rc = xmlTextWriterEndDocument(writer);

std::string memory = reinterpret_cast<char*> buffer->content;
std::cout << memory << std::endl;

xmlFreeTextWriter(writer);
xmlBufferFree(buffer);
```

##  10. <a name='ReadSVG'></a>Read SVG

When you have a `xmlNodePtr` from a xml tree, the following example takes `xmlNodePtr &pNode` as the argument of the function and the following xml:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<svg_content>
<position>1</position>
<svg xmlns="http://www.w3.org/2000/svg" id="1" viewBox="0 0 585 240" preserveAspectRatio="xMidYMid meet">
<rect id="rect_1" x="0" y="0" width="585" height="20" stroke-width="1" stroke="#FFFFFF" fill="#000000"/>
</svg>
</svg_content>
```

`xmlNodeDump` can be used to extract the svg data to be dumped into a svg renderer:

```cpp
xmlNodePtr svgValues = pNode->children;
xmlBufferPtr buffer = xmlBufferCreate();
xmlNodeDump(buffer, pNode->doc, svgValues, 0, 1);
char* value = (char*)buffer->content;
```

##  11. <a name='GettheAttribute'></a>Get the Attribute

The `xmlNode` is the struct used on the tree resulting from the parsing of the xml data. The attribute can be accessed from the `properties`.

```cpp
typedef struct _xmlNode xmlNode;
typedef xmlNode *xmlNodePtr;
struct _xmlNode {
    void           *_private;	/* application data */
    xmlElementType   type;	/* type number, must be second ! */
    const xmlChar   *name;      /* the name of the node, or the entity */
    struct _xmlNode *children;	/* parent->childs link */
    struct _xmlNode *last;	/* last child link */
    struct _xmlNode *parent;	/* child->parent link */
    struct _xmlNode *next;	/* next sibling link  */
    struct _xmlNode *prev;	/* previous sibling link  */
    struct _xmlDoc  *doc;	/* the containing document */

    /* End of common part */
    xmlNs           *ns;        /* pointer to the associated namespace */
    xmlChar         *content;   /* the content */
    struct _xmlAttr *properties;/* properties list */
    xmlNs           *nsDef;     /* namespace definitions on this node */
    void            *psvi;	/* for type/PSVI information */
    unsigned short   line;	/* line number */
    unsigned short   extra;	/* extra data for XPath/XSLT */
};
```

Using the following code:

```cpp
xmlAttrPtr attribute = svgValues->properties;
xmlChar* content = (char*) xmlNodeListGetString(svgValues->doc, attribute->children, 0);
```
##  12. <a name='Checkfilechanged'></a>Check file changed

https://stackoverflow.com/q/14697805/7690982
https://stackoverflow.com/a/1563382/7690982

Use hash functions.