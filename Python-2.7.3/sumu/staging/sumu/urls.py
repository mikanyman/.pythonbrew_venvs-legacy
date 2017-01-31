#from django.conf.urls.defaults import *
#from django.conf.urls.i18n import i18n_patterns
#from django.contrib import admin
#from django.conf import settings

# http://stackoverflow.com/questions/14731988/django-http-500-error
#from django.utils.functional import curry
#from django.views.defaults import *

#source: http://docs.django-cms.org/en/latest/advanced/i18n.html
from django.conf import settings
from django.conf.urls import patterns, include, url
from django.contrib import admin
from django.conf.urls.i18n import i18n_patterns
from django.contrib.staticfiles.urls import staticfiles_urlpatterns


admin.autodiscover()

urlpatterns = patterns('',
    url(r'^jsi18n/(?P<packages>\S+?)/$', 'django.views.i18n.javascript_catalog'),
)

urlpatterns += staticfiles_urlpatterns()

urlpatterns += i18n_patterns('',

    # ---------- external apps statically hooked into urls.py ----------
    #url(r'^polls/', include('polls.urls', namespace="polls")),
    url(r'^exdm/', include('exdm.urls')),
    url(r'^gallery/', include('imagestore.urls', namespace='imagestore')),
    url(r'^ldata/', include('ldata.urls')), # http://sumu.synapse-computing.com/ldata/Astuvansalmi

    url(r'^admin/', include(admin.site.urls)),
    url(r'^', include('cms.urls')), # <--------- include the django cms urls via i18n_patterns

    # ---------- external apps w. namespaces - temp solution ----------
    #url(r'^', include('cms.urls', namespace='polls'))

)

# original
#urlpatterns = i18n_patterns('',
#
    # ---------- external apps statically hooked into urls.py ----------
    #url(r'^polls/', include('polls.urls', namespace="polls")), 
#    url(r'^exdm/', include('exdm.urls')),

#    url(r'^admin/', include(admin.site.urls)),
#    url(r'^', include('cms.urls')),

    # ---------- external apps w. namespaces - temp solution ----------
#    url(r'^', include('cms.urls', namespace='polls'))

#)

#handler500 = curry(server_error, template_name='500.html')


if settings.DEBUG:
    urlpatterns = patterns('',
    url(r'^media/(?P<path>.*)$', 'django.views.static.serve',
        {'document_root': settings.MEDIA_ROOT, 'show_indexes': True}),
    url(r'', include('django.contrib.staticfiles.urls')),
) + urlpatterns
