    <div id="header">
      <div>
        <h1 id="title">{{label}}</h1>
        <div id="homelink">at <a href="{{homelink}}">{{project}}</a></div>
      </div>
      <div class="page-resource-uri"><a href="{{uri.url}}">{{uri}}</a></div>
      <div id="rdficon"><a href="{{data}}" title="RDF data"><img src="http://www.w3.org/RDF/icons/rdf_flyer.24" alt="[This page as RDF]" /></a></div>
    </div>

    {% if depiction %}
        <div class="image"><img src="{{depiction}}" alt="Depiction of {{label}}" /></div>
    {% endif %}

    <table class="description">
      <tr>
        <th style="width: 25%">Property</th>
        <th>Value/s</th>
      </tr>
      {% for prop, values in rows.items %}
      <tr class="{% if forloop.counter|divisibleby:2 %}even{% else %}odd{% endif %}">
        <td class="property">
          <a class="uri" href="{{prop.uri}}" title="{{prop.uri}}">{{prop.label}}</a>
        </td>
        <td>
          <ul>
            {% for value in values%}
            <li>
              {% if value.uri %}
              <a class="uri" href="{{value.url}}" title="{{value.uri}}">{{value.label}}</a>
              {% else %}
              {% if value.literal %}
              <span class="literal">
                {% if value.language %}
                <span xml:lang="{{value.language}}">{{value.literal}}</span> <small>({{value.language}})</small>
                {% else %}
                {{value.literal}}
                {% endif %}
                {% if value.datatype %}
                <small>({{value.datatype}})</small>
                {% endif %}
              </span>
              {% else %}
              {{value}}
              {% endif %}
              {% endif %}
            </li>
            {% endfor %}
          </ul>
        </td>
      </tr>
      {% endfor %}
    </table>

    <div id="footer">
      This page shows information obtained from the SPARQL endpoint at <a class="sparql-uri" href="{{endpoint}}">{{endpoint}}</a>.<br />
      <a href="{{data}}?output=n3">As N3</a> |
      <a href="{{data}}?output=xml">As RDF/XML</a> |
      <a href="http://www4.wiwiss.fu-berlin.de/rdf_browser/?browse_uri={{uri}}">Browse in Disco</a> |
      <a href="http://dig.csail.mit.edu/2005/ajar/ajaw/tab.html?uri={{uri}}">Browse in Tabulator</a> |
      <a href="http://linkeddata.uriburner.com/ode/?uri={{uri}}">Browse in OpenLink Data Explorer</a>
    </div>
