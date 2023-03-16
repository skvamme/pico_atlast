-module(hello_handler).
-behavior(cowboy_handler).

-export([init/2]).

init(Req0, State) ->
	Req = case cowboy_req:method(Req0) of
		<<"GET">> -> 
			#{degrees := Degrees} = cowboy_req:match_qs([{degrees, [], <<>>}], Req0),
			io:format("temperature: ~p~n",[Degrees]), cowboy_req:reply(200, Req0);
		_ -> cowboy_req:reply(503, Req0)
	end,
{ok, Req, State}.

