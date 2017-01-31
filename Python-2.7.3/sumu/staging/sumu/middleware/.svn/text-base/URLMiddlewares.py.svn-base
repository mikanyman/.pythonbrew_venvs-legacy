# http://ilian.i-n-i.org/language-redirects-for-multilingual-sites-with-django-cms/

#from cms.middleware.multilingual import MultilingualURLMiddleware
from django.conf import settings
from django.http import HttpResponseRedirect
from django.utils import translation

class CustomMultilingualURLMiddleware(MultilingualURLMiddleware):

    pass

    """
    def process_request(self, request):
        bla_bla = 'Bla bla'
        lang_path = request.path.split('/')[1]
        if lang_path in settings.URLS_WITHOUT_LANGUAGE_REDIRECT:
            return None
        language = self.get_language_from_request(request)
        translation.activate(language)
        request.LANGUAGE_CODE = language
        if lang_path == '':
            return HttpResponseRedirect('/%s/' % language)
        if len([z for z in settings.LANGUAGES if z[0] == lang_path]) == 0:
            return HttpResponseRedirect('/%s%s' % (language, request.path))
    """
