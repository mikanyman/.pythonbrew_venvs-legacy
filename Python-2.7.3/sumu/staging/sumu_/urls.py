from django.conf.urls.defaults import *
from django.conf.urls.i18n import i18n_patterns
from django.contrib import admin
from django.conf import settings

admin.autodiscover()

urlpatterns = i18n_patterns('',

    # ---------- external apps statically hooked into urls.py ----------
    #url(r'^polls/', include('polls.urls', namespace="polls")), 
    url(r'^exdm/', include('exdm.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^', include('cms.urls')),

    # ---------- external apps w. namespaces - temp solution ----------
    url(r'^', include('cms.urls', namespace='polls'))

)

if settings.DEBUG:
    urlpatterns = patterns('',
    url(r'^media/(?P<path>.*)$', 'django.views.static.serve',
        {'document_root': settings.MEDIA_ROOT, 'show_indexes': True}),
    url(r'', include('django.contrib.staticfiles.urls')),
) + urlpatterns
