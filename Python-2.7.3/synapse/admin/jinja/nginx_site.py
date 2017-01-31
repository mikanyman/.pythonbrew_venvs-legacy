import os, sys
import jinja2

# TO-DO: consider adding to path
sys.path.append('/home/mnyman/.pythonbrew/venvs/Python-2.7.3/synapse/admin') 

def main(argv):

    filename = '/etc/nginx/sites-available/%s' % argv[0]
    if not os.path.isfile(filename):

        # requires that file of type mysite.py exists in conf dictionary
        # TO-DO: add error handling
        exec 'from conf import %s' % argv[0] # argv is a [list]

        templateLoader = jinja2.FileSystemLoader(searchpath='/home/mnyman/.pythonbrew/venvs/Python-2.7.3/synapse/admin/jinja/templates')
        templateEnv = jinja2.Environment(loader=templateLoader)

        TEMPLATE_FILE = 'nginx_site.jinja'
        template = templateEnv.get_template(TEMPLATE_FILE)

        exec "templateVars = {\
            'site': %s.SITE,\
            'status': %s.STATUS,\
            'home_page': %s.HOME_PAGE\
        }" % (argv[0], argv[0], argv[0])

        outputText = template.render(templateVars)

        exec "f = open('../output/%s', 'w')" % argv[0]
        f.write(outputText)
        f.close()

        exec "os.system('sudo mv ../output/%s /etc/nginx/sites-available/%s')" % (argv[0], argv[0])

    else:

        print 'Warning: File \"/etc/nginx/sites-available/%s\" already exists.' % argv[0]

if __name__ == "__main__":
    main(sys.argv[1:])
