from django.conf.urls import patterns, url

urlpatterns = patterns('',
    url(r'^(?P<html>\w+).html/$', 'exdm.views.iframes'),
)
