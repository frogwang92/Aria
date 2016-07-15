import SimpleHTTPServer
import SocketServer

import copylog
import results

PORT = 80

Handler = SimpleHTTPServer.SimpleHTTPRequestHandler

httpd = SocketServer.TCPServer(("", PORT), Handler)

print "serving at port", PORT
print "navigate to http://localhost/amstockchart/ for charts"
httpd.serve_forever()