import os, sys
import jinja2

# TO-DO: consider adding to path
sys.path.append('/home/mnyman/.pythonbrew/venvs/Python-2.7.3/synapse/admin') 

def main(argv):

    # requires that file of type mysite.py exists in conf dictionary
    # TO-DO: add error handling
    exec 'from conf import %s' % argv[0] # argv is a [list]

    templateLoader = jinja2.FileSystemLoader(searchpath='/home/mnyman/.pythonbrew/venvs/Python-2.7.3/synapse/admin/jinja/templates')
    templateEnv = jinja2.Environment(loader=templateLoader)

    TEMPLATE_FILE = 'uwsgi_site.jinja'
    template = templateEnv.get_template(TEMPLATE_FILE)

    exec "templateVars = {\
        'site': %s.SITE,\
        'status': %s.STATUS,\
    }" % (argv[0], argv[0])

    outputText = template.render(templateVars)

    # Assumes that file does not exist
    # TO-DO: create routine "if file exists..."
    # ../output/ relative to location of fabfile.py
    exec "f = open('../output/%s.ini', 'w')" % argv[0]
    f.write(outputText)
    f.close()

if __name__ == "__main__":
    main(sys.argv[1:])
