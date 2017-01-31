from django.shortcuts import render
import urllib2
from django.http import Http404 #, HttpResponse

def get_graph(request, page_name):

    r = 'http://ldata.synapse-computing.com/page/%s' % page_name

    try:
        response = urllib2.urlopen(r)
        graph = response.read()
        context = {
            'graph': graph,
            }
        return render(request, 'djubby/formatted_graph.html', context)

    except urllib2.HTTPError, e:
        if e.code == 404:
            raise Http404
        #if e.code == 500:
        #    raise Http500
        else:
            return HttpResponse("Error")

    #except urllib2.HTTPError, e:
        #print e.code
        #print e.msg
        #print e.headers
        #print e.fp.read()




