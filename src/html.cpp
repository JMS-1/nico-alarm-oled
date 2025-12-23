const char *homePage = "\n\
<html>\n\
\n\
<head>\n\
    <title>Der Nico Alarm</title>\n\
\n\
    <style>\n\
        body,\n\
        html {\n\
            width: 100%;\n\
            height: 100%;\n\
        }\n\
\n\
        body {\n\
            margin: 0;\n\
            background: #eeeeee;\n\
            width: fit-content;\n\
            width: -moz-fit-content;\n\
        }\n\
\n\
        h1 {\n\
            text-align: center;\n\
            margin: 0.5em 0;\n\
        }\n\
\n\
        .options {\n\
            overflow: auto;\n\
            row-gap: 1em;\n\
            padding: 1em;\n\
        }\n\
\n\
        button {\n\
            font-size: 2em;\n\
            border-radius: 8px;\n\
            padding: 0.5em;\n\
            background: #cccccc;\n\
            border-width: 3px;\n\
            margin: 0.5em;\n\
            outline: unset !important;\n\
        }\n\
\n\
        button.center-red {\n\
            color: #ff0000;\n\
        }\n\
\n\
        button.center-green {\n\
            color: #00a000;\n\
        }\n\
\n\
        button.center-yellow {\n\
            color: #ffff00;\n\
        }\n\
\n\
        button.ring-red {\n\
            border-color: #ff0000;\n\
        }\n\
\n\
        button.ring-green {\n\
            border-color: #00a000;\n\
        }\n\
\n\
        button.ring-yellow {\n\
            border-color: #ffff00;\n\
        }\n\
    </style>\n\
\n\
    <script>\n\
        function request(what) {\n\
            const xhr = new XMLHttpRequest()\n\
\n\
            xhr.open('GET', '/' + what)\n\
\n\
            xhr.send()\n\
        }\n\
\n\
        function off() {\n\
            return request('OFF?text=aus')\n\
        }\n\
\n\
        function rr() {\n\
            return request('RR?text=rot-rot')\n\
        }\n\
\n\
        function rg() {\n\
            return request('RG?text=rot-gr%C3%BCn')\n\
        }\n\
\n\
        function ry() {\n\
            return request('RY?text=rot-gelb')\n\
        }\n\
\n\
        function gr() {\n\
            return request('GR?text=gr%C3%BCn-rot')\n\
        }\n\
\n\
        function gg() {\n\
            return request('GG?text=gr%C3%BCn-gr%C3%BCn')\n\
        }\n\
\n\
        function gy() {\n\
            return request('GY?text=gr%C3%BCn-gelb')\n\
        }\n\
\n\
\n\
        function yr() {\n\
            return request('YR?text=gelb-rot')\n\
        }\n\
\n\
        function yg() {\n\
            return request('YG?text=gelb-gr%C3%BCn')\n\
        }\n\
\n\
        function yy() {\n\
            return request('YY?text=gelb-gelb')\n\
        }\n\
    </script>\n\
</head>\n\
\n\
<body>\n\
    <h1>Der Nico Alarm</h1>\n\
    <div class='options'>\n\
        <div>\n\
            <button onclick='off()'>Ausschalten</button>\n\
        </div>\n\
        <div>\n\
            <button onclick='rr()' class='center-red ring-red'>Leiser bitte</button>\n\
            <button onclick='gr()' class='center-green ring-red'>Essen ist fertig</button>\n\
        </div>\n\
        <div>\n\
            <button onclick='rg()' class='center-red ring-green'>Bitte melden</button>\n\
            <button onclick='yg()' class='center-yellow ring-green'>Besuch ist da</button>\n\
        </div>\n\
        <div>\n\
            <button onclick='ry()' class='center-red ring-yellow'>Gleich wird es laut</button>\n\
            <button onclick='gy()' class='center-green ring-yellow'>Anruf erwartet</button>\n\
        </div>\n\
    </div>\n\
</body>\n\
\n\
</html>\n\
";

const char *getHomePage(void)
{
    return homePage;
}
