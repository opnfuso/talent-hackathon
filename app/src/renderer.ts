/* eslint-disable @typescript-eslint/no-var-requires */
// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process unless
// nodeIntegration is set to true in webPreferences.
// Use preload.js to selectively enable features
// needed in the renderer process.
const axios = require("axios");

const token =
  "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJpYXQiOjE2ODA3Mzg3MTksImV4cCI6MTY4MjQ2NjcxOSwianRpIjoiWENLUm5nQk5KdGRNIiwiYXBwbGljYXRpb25faWQiOiJhYjIyMmY3Zi1kYzQyLTQwOTQtYTUzOS03ZDQxNzEwNGM5MjciLCJzdWIiOiIiLCJhY2wiOiIifQ.NwQhXIgps12nw4SB7O4_hFzRva6pzRHpm-CBNhgsQK6KFcMaThNa_4Xu-Eats6PT2DPr5WemSoWVLBRVdrVuPocipjxSjCbbv7OvZy7WCMs5ZLz5UzESuhN9e0aiM1EpllB6B8Z8VAKV6Avup-DLv_NNoXsNElUCG00JLLWD0QV6kZlXJWftTdDIa2pKPg06vaS1eSQ7xds9OawNwHACfKS5Y3CiTD10aW_Kp5wF5H7_zP0cQsKDc7koCbJdWXtVFoKyXIUwFHFoKrPlKs0Is37U5LjoucukNkgTXxJgaqo_HVply2ELJe3pWWt-s1OLpgUKnzabeMVxqg-TtnkdsQ";

const config = {
  headers: { Authorization: `Bearer ${token}` },
};

let callId: string;

async function makeCall() {
  const response = await axios.post(
    "https://api.nexmo.com/v1/calls/",
    {
      ncco: [
        {
          action: "stream",
          streamUrl: [
            "https://github.com/anars/blank-audio/blob/master/1-hour-and-20-minutes-of-silence.mp3?raw=true",
          ],
          loop: 0,
          level: -1,
        },
      ],
      to: [
        {
          type: "phone",
          number: "5213310819243",
          // number: "5213320683941",
        },
      ],
      from: {
        type: "phone",
        number: "5213310819243",
        // number: "5213320683941",
      },
    },
    config
  );

  callId = response.data.uuid;
}

async function sendTone(tone: string, callId: string) {
  axios.put(
    `https://api.nexmo.com/v1/calls/${callId}/dtmf`,
    {
      digits: tone,
    },
    config
  );
}

async function hungUpCall(callId: string) {
  axios.put(
    `https://api.nexmo.com/v1/calls/${callId}`,
    {
      action: "hangup",
    },
    config
  );
}

const $callBtn = document.getElementById("llamar");

const $hungUpBtn = document.getElementById("colgar");

function delay(ms: number) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

$callBtn.addEventListener("click", () => {
  alert("Iniciando conexión");
  makeCall();
  $callBtn.setAttribute("disabled", "");
  $hungUpBtn.removeAttribute("disabled");
});

$hungUpBtn.addEventListener("click", () => {
  alert("Terminando conexión");
  hungUpCall(callId);
  $hungUpBtn.setAttribute("disabled", "");
  $callBtn.removeAttribute("disabled");
});

const $btn1 = document.getElementById("1");
const $btn2 = document.getElementById("2");
const $btn3 = document.getElementById("3");
const $btn4 = document.getElementById("4");
const $btn5 = document.getElementById("5");
const $btn6 = document.getElementById("6");
const $btn7 = document.getElementById("7");
const $btn8 = document.getElementById("8");
const $btn9 = document.getElementById("9");
const $btna1 = document.getElementById("a1");
const $btna2 = document.getElementById("a2");
const $btna3 = document.getElementById("a3");
const $btna4 = document.getElementById("a4");
const $btnRGB1 = document.getElementById("b1");
const $btnRGB2 = document.getElementById("b2");
const $btnRGB3 = document.getElementById("b3");
const $btnRGB4 = document.getElementById("b4");
const $btnRGB5 = document.getElementById("b5");
const $btnRGB6 = document.getElementById("b6");
const $btnRGB7 = document.getElementById("b7");
const $btnRGB8 = document.getElementById("b8");

$btn1.addEventListener("click", () => sendTone("1", callId));
$btn2.addEventListener("click", () => sendTone("2", callId));
$btn3.addEventListener("click", () => sendTone("3", callId));
$btn4.addEventListener("click", () => sendTone("4", callId));
$btn5.addEventListener("click", () => sendTone("5", callId));
$btn6.addEventListener("click", () => sendTone("6", callId));
$btn7.addEventListener("click", () => sendTone("7", callId));
$btn8.addEventListener("click", () => sendTone("8", callId));
$btn9.addEventListener("click", () => sendTone("9", callId));
$btna1.addEventListener("click", () => sendTone("0*", callId));
$btna2.addEventListener("click", () => sendTone("0#", callId));
$btna3.addEventListener("click", () => sendTone("00", callId));
$btna4.addEventListener("click", () => sendTone("05", callId));
$btnRGB1.addEventListener("click", () => {
  sendTone("*1", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB2.addEventListener("click", () => {
  sendTone("*2", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB3.addEventListener("click", () => {
  sendTone("*3", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB4.addEventListener("click", () => {
  sendTone("*4", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB5.addEventListener("click", () => {
  sendTone("*5", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB6.addEventListener("click", () => {
  sendTone("*6", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB7.addEventListener("click", () => {
  sendTone("*7", callId);
  delay(3000).then(() => sendTone("5", callId));
});
$btnRGB8.addEventListener("click", () => {
  sendTone("*8", callId);
  delay(3000).then(() => sendTone("5", callId));
});
