
#!/usr/bin/env python3
"""
Very simple HTTP server in python for logging requests
Usage::
    ./server.py [<port>]
"""
from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
import fcntl
import termios
from sys import argv
from subprocess import check_output

def get_pid():
    return check_output(["pidof","dico"])


def isonlist(domain):

    pid=get_pid().decode('utf-8').strip()
    if pid is None:
        return -1

    with open(f'/proc/{pid}/fd/0', 'w') as fd:
        for char in domain+"\n":
            fcntl.ioctl(fd, termios.TIOCSTI, char)

    f=open("../phising_website_grapper/history.txt","r").read().splitlines()
    if domain+"=1" in f:
        return 1
    elif domain+"=0" in f:
        return 0
    else:
        return -2


class S(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')

        self.end_headers()

    def do_GET(self):
        logging.info("GET request,\nPath: %s\nHeaders:\n%s\n", str(self.path), str(self.headers))
        print(f"PATH HERE=>{self.path}")
        self._set_response()
        if 'd=' in self.path:
            splitted=self.path.split('=')[1]
            print("DOMAIN",splitted)
            print("RESULT IS ",isonlist(splitted))
        
            logging.info("GET request,\nPath: %s\nHeaders:\n%s\n",
                str(self.path), str(self.headers))

            self.wfile.write("{}".format(str(isonlist(splitted))).encode('utf-8'))
        

        #self.wfile.write("GET request for {}".format(self.path).encode('utf-8'))

    def do_POST(self):
        content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
        post_data = self.rfile.read(content_length) # <--- Gets the data itself
        logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",
                str(self.path), str(self.headers), post_data.decode('utf-8'))

        self._set_response()
        self.wfile.write("POST request for {}".format(self.path).encode('utf-8'))

def run(server_class=HTTPServer, handler_class=S, port=8080):
    logging.basicConfig(level=logging.INFO)
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    logging.info('Starting httpd...\n')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    logging.info('Stopping httpd...\n')

if __name__ == '__main__':

    if(len(argv)==2):
        run(port=int(argv[1]))
    else:
        run()