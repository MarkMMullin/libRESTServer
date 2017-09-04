#include "file_resources.hpp"
Html_file htmlfile__index_html;
Html_file htmlfile__test_file_root_html;
Html_file htmlfile__test_test_file_html;
Html_file htmlfile__test_directory_updates_file_html;
Html_file htmlfile__404;
Html_file htmlfile__OK;


void initializeFiles()
{
  initializeTextFile(&htmlfile__index_html,
    "index.html",
    "/",
    "<!Doctype html>\n"
    "\n"
    "<html>\n"
    "<head>\n"
    "	<meta charset=\"utf-8\">\n"
    "	<title>Page layout 2</title>\n"
    "	<style>\n"
    "		body {\n"
    "			font: 80% arial, helvetica, sans-serif;\n"
    "			margin: 0;\n"
    "		}\n"
    "		\n"
    "		#navigation {\n"
    "			position: absolute;\n"
    "			left: 0;\n"
    "			width: 15em;\n"
    "		}\n"
    "\n"
    "		#content {\n"
    "			margin-left: 15em;\n"
    "		}\n"
    "		\n"
    "		\n"
    "	</style>\n"
    "</head>\n"
    "\n"
    "<body>\n"
    "\n"
    "	<div id=\"navigation\">\n"
    "\n"
    "		<ul>\n"
    "			<li><a href=\"/test_file_root.html\">Test file</a></li>\n"
    "            <li><a href=\"/test/directory/updates/file.html\">Updates</a></li>\n"
    "			<li><a href=\"\">Natural Selection</a></li>\n"
    "			<li><a href=\"\">Genetics</a></li>\n"
    "		</ul>\n"
    "\n"
    "		<ul>\n"
    "			<li><a href=\"\">Erasmus Darwin</a></li>\n"
    "			<li><a href=\"\">Lamarck</a></li>\n"
    "			<li><a href=\"\">Charles Darwin</a></li>\n"
    "			<li><a href=\"\">Wallace</a></li>\n"
    "			<li><a href=\"\">Dawkins</a></li>\n"
    "		</ul>\n"
    "\n"
    "	</div>\n"
    "</body>\n"
    "\n"
                     "</html>\n",
                     "text/html; charset=UTF-8\n"
		     );

  initializeTextFile(&htmlfile__test_file_root_html,
    "test_file_root.html",
    "/",
    "<html>\n"
    "    <body>\n"
    "        <p>\n"
    "    Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod\n"
    "tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At\n"
    "vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren,\n"
    "no sea takimata sanctus est Lorem ipsum dolor sit amet.\n"
    "        </p>\n"
    "    </body>\n"
                     "</html>\n",
                     "text/html; charset=UTF-8"
		     );

  initializeTextFile(&htmlfile__test_test_file_html,
    "test_file.html",
		     "/test",
		     "",
                     "text/html; charset=UTF-8"
		     );

  initializeTextFile(&htmlfile__test_directory_updates_file_html,
    "file.html",
    "/test/directory/updates",
    "<html>\n"
    "    <body>\n"
    "        <p>\n"
    "        <h1>For example, here should be data from sensors.</h1>\n"
    "        </p>\n"
    "    </body>\n"
                     "</html>\n",
                     "text/html; charset=UTF-8"
		     );

  initializeTextFile(&htmlfile__404,
    "404.html",
    "/",
    "<html>\n"
    "    <body>\n"
    "        <p>\n"
    "        <h1>404 Not Found</h1>\n"
    "        </p>\n"
    "    </body>\n"
                     "</html>\n",
                     "text/html; charset=UTF-8"
		     );

                    

  initializeTextFile(&htmlfile__OK,
    "OK.html",
    "/",
    "<html>\n"
    "    <body>\n"
    "        <p>\n"
    "        <h1>OK</h1>\n"
    "        </p>\n"
    "    </body>\n"
                     "</html>\n",
                     "text/html; charset=UTF-8"
		     );

                    
}

std::unordered_map<std::string, Html_file*> populate_file_umap()
{
    std::unordered_map<std::string, Html_file*> file_hash_table;
    file_hash_table["/"]                                 = &htmlfile__index_html;
    file_hash_table["/index.html"]                       = &htmlfile__index_html;
    file_hash_table["/test_file_root.html"]              = &htmlfile__test_file_root_html;
    file_hash_table["/test/directory/updates/file.html"] = &htmlfile__test_directory_updates_file_html;
    file_hash_table["/404.html"] = &htmlfile__404;
    file_hash_table["/OK.html"] = &htmlfile__OK;
    return file_hash_table;
}
