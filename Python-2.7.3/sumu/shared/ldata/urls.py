from django.conf.urls import patterns, url, include

urlpatterns = patterns('',
    (r'^(.*)', 'djubby.dispatcher'),
)



