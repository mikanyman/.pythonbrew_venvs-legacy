from fabric.api import local
import os

def hello():
    print('Hello World!')


def config_nginx(site):
    """ call by fab config_nginx:site=mysite """
    local('python ../jinja/nginx_site.py %s' % (site,))

def config_uwsgi(site):
    """ call by fab config_uwsgi:site=mysite """
    local('python ../jinja/uwsgi_site.py %s' % (site,)) # creates file <site> in ../output/

