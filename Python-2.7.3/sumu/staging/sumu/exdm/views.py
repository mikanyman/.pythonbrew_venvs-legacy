from django.shortcuts import render
import settings

def iframes(request, html):

    html_path = settings.PROJECT_PATH + '/sitestatic/easyxdm/' + html + '.html'
    context = {'html_path': html_path}
    return render(request, 'exdm/wrapper.html', context)

