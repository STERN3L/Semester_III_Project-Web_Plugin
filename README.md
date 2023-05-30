# Web Plugin

Web security packets plugin

## Description

Web security packets plugin



## Warning

The part concerning MQTT is not functional at the moment. Functional folders are: extension/, http_server, phishing_website_grapper/.

## Installation

1) Clone this repo

```bash
git clone https://github.com/STERN3L/Semester_III_Project-Web_Plugin
```

2) Generate "dico" binary

```bash
cd phising_website_grapper && make
```

## Usage

Load the extension in Firefox : 
 - Launch Firefox
 - Navigate to "about:debugging"
 - click on "this firefox"
 - click on "Load temporary add-on"
 - Select the "manifest.json" file

The add-on is now loaded on your firefox

Launch the web server (*sudo is mandatory*):

```bash
sudo python3 http_server/main.py
```

The web server is now waiting for your requests

Run the binary that checks if a site is in the phishing site hashtable :

```bash
cd phising_website_grapper && ./dico
```

You're done !

The extension will intercept your request and send it to the web server, which will call "dico" to check whether the site is blacklisted or not. The http server will then return the answer and your extension will act accordingly.

Sites considered as phishing sites are listed in phising_website_grapper/phising_site.txt

## Authors and acknowledgment

This project is developed by :
- BAZAIN Danyil
- BINAND Nicolas
- MITTA Chems
- JAEN Maxime


