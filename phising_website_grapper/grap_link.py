from bs4 import BeautifulSoup
import urllib.request

# GET LINE AND PHISING URL FROM THE WEBSITE

url = "https://openphish.com/feed.txt"
ourUrl = urllib.request.urlopen(url)

soup=BeautifulSoup(ourUrl,'html.parser')

text = soup.prettify()
ListeSite = []



# LIRE DE FICHIER
FileRead = open("phising_site.txt","r")
contenu = FileRead.read()

File = []
for FileLine in contenu.split('\n'):
    File.append(FileLine)



for line in text.split('\n'):
    if line not in File:
        print("[+] Line not in txt file, we can add it ! The line is : ",line)
        ListeSite.append(line)
    else:
        print("[-] Already in txt file ! The line is : ",line)
        
FileRead.close()


FileWrite = open("phising_site.txt","a")

for final in ListeSite :
    final += '\n'
    FileWrite.write(final)
    print("[+] Line ",final," is add in the txt file !")




FileWrite.close()