import sugar
import asynchttpserver except Request
import std/re
import std/strutils

type HttpMethod = enum
  Unknown, All, Get, Post, Put, Delete, Patch, Head, Options

type PathToRegExpOptions = object
  sensitive: bool
  strict: bool
  `end`: bool

type Request = object
  path: string

type Response = object
  status: uint16

type Key = object
  name: string
  optional: bool
  offset: int
  index: int

proc pathToRegExpString(registered_path: string, keys: var seq[Key], op: PathToRegExpOptions, parent_path: string): string =
  var regex = "^" & parent_path & registered_path
  var key_index = 0
  var start_pos = 0
  while (start_pos != -1):
    start_pos = find(regex, ":", start_pos)
    if (start_pos != -1):
      var dash_end_pos = find(regex, "-", start_pos)
      var next_end_pos = find(regex, ":", start_pos + 1)
      var slash_end_pos = find(regex, "/", start_pos)
      var end_pos = min(min(dash_end_pos, slash_end_pos), next_end_pos)
      var tmp_key = Key()
      var key_name = regex[start_pos + 1 .. end_pos]
      if (key_name == ""):
        var e: ref OSError # TODO
        new(e)
        e.msg = "Empty parameter name found in path: " & registered_path
        raise e
      key_index = key_index + 1
      tmp_key.index = key_index
      tmp_key.name = key_name
      regex[start_pos .. end_pos] = "(\\S+)"
      keys.add(tmp_key)
  if (op.`end`):
    regex = regex & "$"
  elif (op.strict):
    regex = regex & "/\\S*"
  else:
    regex = regex & "\\S*"
  return regex

type
  HandlerType = enum
    WithNext, WithoutNext
  Handler = ref object
    case kind: HandlerType
    of WithNext: handlerWithNext: (Request, Response, NextRouter) -> void
    of WithoutNext: handlerWithoutNext: (Request, Response) -> void
  Route = ref object
    path: string
    stack: seq[Layer]
    methods: set[HttpMethod]
  Layer = object
    path: string
    regexp: Regex
    route: Route
    keys: seq[Key]
    options: PathToRegExpOptions
    `method`: HttpMethod
    handler: (Request, Response, NextRouter) -> void
  Router = object
    routes: seq[Route]
    stack: seq[Layer]
    parent_path: string
    case_sensitive: bool
  NextRouter = object
    req: Request
    res: Response
    router: Router
method dispatch(this: Route, req: Request, res: Response, next: NextRouter)
method handleRequest(this: Layer, req: Request, res: Response, next: NextRouter) =
  if this.route == nil:
    this.handler(req, res, next)
  else:
    this.route.dispatch(req, res, next)
method dispatch(this: Route, req: Request, res: Response, next: NextRouter) =
  for l in this.stack:
    l.handleRequest(req, res, next)
method init(this: var Layer, registered_path: string, options: PathToRegExpOptions, parent_path: string, handler: Handler): Layer =
  this.path = registered_path
  this.options = options
  this.regexp = re(pathToRegExpString(this.path, this.keys, options, parent_path))
method createRoute(this: var Router, registered_path: string): Route =
  let r = Route(path: registered_path)
  let op = PathToRegExpOptions(sensitive: this.case_sensitive, strict: true, `end`: true)
  var l = Layer()
  l = l.init(registered_path, op, this.parent_path, Handler(kind: WithNext, handlerWithNext: (req: Request, res: Response, next: NextRouter) => (
    l.route.dispatch(req, res, next)
  )))
  l.route = r
  this.stack.add(l)
  return r
method registerPath(this: var Router, registered_path: string, `method`: HttpMethod, handler: Handler): void =
  let route = this.createRoute(registered_path)
  let op = PathToRegExpOptions(sensitive: false, strict: false, `end`: true)
  var layer = Layer()
  layer = layer.init("/", op, this.parent_path, handler)
  layer.`method` = `method`
  route.methods.incl(`method`)
  route.stack.add(layer)
method get(this: var Router, path: string, handler: Handler): Router =
  this.registerPath(path, HttpMethod.Get, handler)
  return this

type NimExpress* = object
  router*: Router
  server*: AsyncHttpServer
  routes: seq[Route]
method get(this: var NimExpress, registered_path: string, handler: Handler): void =
  discard this.router.get(registered_path, handler)

when isMainModule:
  var app = NimExpress()

  app.get("/", Handler(kind: WithoutNext, handlerWithoutNext: (req: Request, res: Response) => (
    discard
  )));
