-module(webserver_app).
-behaviour(application).

-export([start/2]).
-export([stop/1]).

start(_Type, _Args) ->
	Dispatch = cowboy_router:compile([
        {'_', [
		{"/", hello_handler, []},
		{"/atl/[...]", cowboy_static, {priv_dir, webserver, "static/atl",
		[{mimetypes, {<<"text">>, <<"html">>, []}}]}}
		]}
    ]),
    {ok, _} = cowboy:start_clear(my_http_listener,
        [{port, 8080}],
        #{env => #{dispatch => Dispatch}}
    ),
	webserver_sup:start_link().

stop(_State) ->
	ok.


