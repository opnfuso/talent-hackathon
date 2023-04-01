const express = require("express");
const app = express();
const server = require("http").Server(app);
const url = require("url");

const WebSocket = require("ws");

const port = process.env.PORT || 3000;

const express_config = require("./config/express.js");

express_config.init(app);

const wss1 = new WebSocket.Server({ noServer: true });
const wss2 = new WebSocket.Server({ noServer: true });

function heartbeat() {
  this.isAlive = true;
}

//esp32cam websocket
wss1.on("connection", function connection(ws) {
  ws.isAlive = true;
  ws.on("error", console.error);
  ws.on("pong", heartbeat);
  ws.on("message", function incoming(message) {
    wss2.clients.forEach(function each(client) {
      if (client.readyState === WebSocket.OPEN) {
        client.send(message);
      }
    });
  });
});

const interval = setInterval(function ping() {
  wss1.clients.forEach(function each(ws) {
    if (ws.isAlive === false) {
      wss2.clients.forEach((ws) => {
        ws.send("terminated");
      });
      return ws.terminate();
    }

    ws.isAlive = false;
    ws.ping();
  });
}, 2000);

wss1.on("close", function close() {
  clearInterval(interval);
});

//webbrowser websocket
wss2.on("connection", function connection(ws) {
  console.log("connection");
  ws.on("message", function incoming(message) {
    // nothing here should be received
    console.log("received wss2: %s", message);
  });
});

server.on("upgrade", function upgrade(request, socket, head) {
  const pathname = url.parse(request.url).pathname;

  if (pathname === "/jpgstream_server") {
    wss1.handleUpgrade(request, socket, head, function done(ws) {
      wss1.emit("connection", ws, request);
    });
  } else if (pathname === "/jpgstream_client") {
    wss2.handleUpgrade(request, socket, head, function done(ws) {
      wss2.emit("connection", ws, request);
    });
  } else {
    socket.destroy();
  }
});

app.get("/", (req, res) => {
  res.render("index", {});
});

server.listen(port, () => {
  console.log(`App listening at http://localhost:${port}`);
});
