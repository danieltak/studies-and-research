<!-- vscode-markdown-toc -->
* 1. [Sistema Operacional](#SistemaOperacional)
	* 1.1. [Linux vs Windows for Server](#LinuxvsWindowsforServer)
	* 1.2. [Distribuição Linux](#DistribuioLinux)
	* 1.3. [Debian vs Ubuntu](#DebianvsUbuntu)
	* 1.4. [KDE vs GNOME](#KDEvsGNOME)
* 2. [Site Estático](#SiteEsttico)
* 3. [Hugo vs Gatsby](#HugovsGatsby)
	* 3.1. [Hugo Template](#HugoTemplate)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

# Choices

##  1. <a name='SistemaOperacional'></a>Sistema Operacional

Quando se trata de SO para desktop, como engenheiro e funcionário do mundo corporativo, a escolha sempre foi o Windows, pela compatibilidade com os softwares utilizados. Mas para programação o Linux pode ser uma alternativa em muitos casos, mas em empresas a TI normalmente liberará somente o Windows.

Já para servidores este cenário é um pouco diferente.

###  1.1. <a name='LinuxvsWindowsforServer'></a>Linux vs Windows for Server

Como usuário de Open Source e que não gostaria de gastar muito dinheiro com licenças, a opção de Linux é óbvia.

Mas vamos analisar um pouco as vantagens de Windows. Possui suporte e hotline, amplamente utilizado, com muitos profissionais para prestar serviço de suporte, muitos dos softwares pagos e validados em corporações possuem maior compatibilidade com Windows. Ou seja, é um ganha pão melhor para possuir clientes ou um trabalho. A maioria das vezes a escolha deste SO é pela transferência responsabilidade para a prestadora de serviços e não se preocupar com o SO, que é algo complexo e muitas vezes não é necessário uma equipe ou colaborador para prestar suporte ao SO.

Uma grande desvantagem que presenciei na vida profissional, muitos detalhes são extremamente específicos do Windows e há pouca informação sobre estes detalhes mais incomuns. Um "dinossauro" da área foi consultado e muitos problemas foram resolvidos, porém estas informações não estavam documentadas ou facilmente encontradas.

A escolha para alguém que não possui muito dinheiro seria o Linux,  correto? Sim, mas qual das distribuições?

###  1.2. <a name='DistribuioLinux'></a>Distribuição Linux

RHEL (Red Hat) é pago e a fundação terminou o projeto de desenvolvimento do CentOS ( Open source ) em 2020. Por vários motivos, mas esse era a alternativa mais utilizada do mercado. Recentemente compraram o Fedora e muitos cogitam a possibilidade do Red Hat Foundation matar este SO também.

Pelo que pesquisei as mais utilizadas recentemente são Ubuntu Server e Debian.

###  1.3. <a name='DebianvsUbuntu'></a>Debian vs Ubuntu

O Ubuntu é um fork do Debian que está na versão mais instável, porém é mais atualizado e possui funcionalidades mais novas. Recomendado para o usuário que trabalha com pesquisas ou projetos ultra modernos e necessita de recursos mais recentes, inclusive drivers para hardwares que lançaram recentemente.

Já o Debian lança um release estável com mais tempo e testes, portanto, alguns recursos são desatualizados, por outro lado, é muito mais estável.

Como meu foco é possuir um servidor estável, com utilização de recursos estáveis e testados, que não me dê problemas e com um Hardware mais barato. A escolha do Debian ficou fácil.

Mas instalar um servidor com GUI? Se sim, qual a escolha do ambiente gráfico?

Debian and Ubuntu are two popular Linux distributions used as both desktop and server operating systems. Both are open-source distros with excellent reputations and sizable user bases. However, there are some differences between the two that make one or the other better suited for certain use cases.

Debian is among the oldest and most reliable Linux distros on the market. It is the go-to choice for environments that prioritize system stability and security, such as production servers. Debian’s long-term support and reliability make it a preferred option for servers that require uninterrupted, surprise-free operation. The Debian security team has a proven track record of effective and timely security patches. Debian’s package manager (the Advanced Package Tool, or APT for short) simplifies software installations and updates. Debian is a community-driven project, so there’s no commercial entity behind this Linux distro.

Ubuntu, on the other hand, is a more user-friendly and versatile distro that is better suited for desktop use. It is based on Debian and shares many of its features, but it has a faster release cycle and is more cutting-edge. Ubuntu is a good choice for servers that require the latest features and software updates. It also has a larger user base and more commercial support options than Debian.

In summary, if you prioritize stability and security over new features and software updates, Debian is the better choice for your server. If you want a more user-friendly and versatile distro that is better suited for desktop use, Ubuntu is the way to go.

###  1.4. <a name='KDEvsGNOME'></a>KDE vs GNOME

O GNOME possui um design moderno e diferente, porém menos ferramentas.

Como programador de Qt, com o KDE eu consigo contribuir, utilizar as múltiplas ferramentas oferecidas pela comunidade e possui um design mais parecido com o do Windows. Tudo isso, consumindo menos recursos.

KDE and GNOME are two popular desktop environments for Linux operating systems. Both have their own strengths and weaknesses, and the choice between them depends on your personal preferences and requirements.

KDE is known for its rich feature set and customizability. It offers a traditional desktop layout that is comfortable for most Windows users. KDE’s consistent look and feel, even with numerous improvements over the years, is one of its strengths. KDE is also known for its freedom in setting and designing applications.

GNOME, on the other hand, provides a unique and modern user interface design. It is a good choice if you want a different desktop experience. GNOME’s icons, themes, and wallpapers may look better regarding modern standards. However, adjusting the workflow could take a while if you are already comfortable with the traditional Windows-like layout. GNOME is known for its fanbase and community support.

In summary, KDE is a good choice if you prioritize customizability and a traditional desktop layout. GNOME is a good choice if you want a unique and modern user interface design.

##  2. <a name='SiteEsttico'></a>Site Estático

Static pages are a great choice for projects with simple needs and limited resources. They are quick and easy to create, cheap to host, secure, and require less management and maintenance.

A static website is a website that serves pages using a fixed number of pre-built files composed of HTML, CSS, and JavaScript. A static website has no backend server-side processing and no database. Any “dynamic” functionality associated with the static site is performed on the client side, which means the code is executed in visitors’ browsers rather than on the server. In non-technical terms, this means that your hosting delivers the website files to visitors’ browsers exactly as those files appear on the server. What’s more, every single visitor gets the same static file delivered to their browsers, which means largely having the exact same experiences and seeing the exact same content.

Static websites are a good choice for small businesses, personal blogs, portfolios, and other sites that don’t require frequent updates or complex functionality. They are also a good choice for sites that need to load quickly and have a low bandwidth requirement. Static websites can be built using a variety of tools, including static site generators, headless CMSs, and even plain HTML, CSS, and JavaScript.

In summary, static pages are a great choice for simple websites that don’t require frequent updates or complex functionality. They are quick and easy to create, cheap to host, and secure.

##  3. <a name='HugovsGatsby'></a>Hugo vs Gatsby

Hugo and Gatsby are two popular static site generators used to create static websites. Both have their own strengths and weaknesses, and the choice between them depends on your personal preferences and requirements.

Hugo is a static site generator written in Go. It takes data files, i18n bundles, configuration, templates for layouts, static files, and content written in Markdown and renders a static website. Hugo is known for its speed and simplicity. It is a good choice if you want to create a relatively simple blog or website. However, if you want to extend it, you’ll need to take the time to learn its magic.

Gatsby, on the other hand, is a static site generator based on React. It is a good choice if you want to create a more complex website with dynamic content. Gatsby is known for its speed, performance, and modern web development features. It has a large and active community that provides a wide range of plugins and themes. Gatsby is a good choice if you want to create a website that is fast, scalable, and easy to maintain.

In summary, Hugo is a good choice if you want to create a relatively simple blog or website, while Gatsby is a good choice if you want to create a more complex website with dynamic content.

I wanted to use Gatsby, since I am learning React, but Hugo community, templates and simplicity was the factor of choice. Since Gatsby seems to be going to a paid direction, which is not wrong, but I want a simple dev Blog that is generated from MarkDown without much customizations.

Gatsby is a complete tool to make static pages, with plugins for most used CMS (Wordpress, Drupal, Shopify, etc. ), but it was too much for my needs and what i learned in programming is:

> Most of the times, simplicity is bliss.

For a low cost static page blog, Hugo seemed the best choice and the template that looked more complete was [PaperMod](https://github.com/adityatelange/hugo-PaperMod).



https://dev.to/bholmesdev/before-building-your-next-static-site-with-react-consider-this-2b60

### Astro

https://www.accessible-astro.dev/

https://github.com/onwidget/astrowind