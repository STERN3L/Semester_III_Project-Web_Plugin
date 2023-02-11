from bs4 import BeautifulSoup
import urllib.request

# GET LINE AND PHISING URL FROM THE WEBSITE

url = "https://openphish.com/feed.txt"
ourUrl = urllib.request.urlopen(url)

soup=BeautifulSoup(ourUrl,'html.parser')

text = soup.prettify()
ListeSite = []


i = 0
y = 0

# LIRE DE FICHIER
FileRead = open("phising_site.txt","r")
contenu = FileRead.read()

File = []
for FileLine in contenu.split('\n'):
    File.append(FileLine)



for line in text.split('\n'):
    if len(line) == 0:
        pass
    else:
        Aline = line.split("://", 1)
        Bline = Aline[1]
        Cline = Bline.split("/", 1)
        line = Cline[0]
        if "www." in line :
            Atext = line.split("www.", 1)
            line = Atext[1]
        if line not in File:
            print("[+] Line not in txt file, we can add it ! The line is : ",line)
            ListeSite.append(line)
        else:
            y = y + 1
print("[-] ",y," Line already in txt file !")
        
FileRead.close()

ListeSite = sorted(ListeSite)

FileWrite = open("phising_site.txt","a")

for final in ListeSite :
    final += '\n'
    FileWrite.write(final)
    i = i+1
print("[+] ",i,"Line added in the txt file !")




FileWrite.close()
