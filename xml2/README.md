<!-- vscode-markdown-toc -->
* 1. [Introduction](#Introduction)
* 2. [xmlParser vs xmlReader](#xmlParservsxmlReader)
* 3. [Casting xmlChar](#CastingxmlChar)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

##  1. <a name='Introduction'></a>Introduction

https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/general.html

Tutorials http://www.xmlsoft.org/examples/


free xml buffer and doc

##  2. <a name='xmlParservsxmlReader'></a>xmlParser vs xmlReader

Although the [official tutorial](https://gnome.pages.gitlab.gnome.org/libxml2/tutorial/index.html) suggests the use of the function xmlParseFile(), it isn't recommended, use xmlReader instead. It is more powerful, [answers on Stack Overflow](https://stackoverflow.com/questions/19315206/xmlparsefile-vs-xmlreadfile-libxml2) also suggest the use of the function.

The [official documentation](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-parser.html#xmlParseFile) states that xmlParseFile is deprecated and recommends the use of [xmlReadFile](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-parser.html#xmlReadFile) instead.

However, the newer [xmlReader](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-xmlreader.html) is a better choice, even though there are lots old tutorials using xmlParseFile. Mainly when [used to parse big files](https://stackoverflow.com/a/23403898/7690982).


##  3. <a name='CastingxmlChar'></a>Casting xmlChar

