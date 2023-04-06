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
          number: "5213320683941",
        },
      ],
      from: {
        type: "phone",
        number: "5213320683941",
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
const $btn10 = document.getElementById("10");
const $btn0 = document.getElementById("0");
const $btn12 = document.getElementById("12");

$btn1.addEventListener("click", () => sendTone("1", callId));
$btn2.addEventListener("click", () => sendTone("2", callId));
$btn3.addEventListener("click", () => sendTone("3", callId));
$btn4.addEventListener("click", () => sendTone("4", callId));
$btn5.addEventListener("click", () => sendTone("5", callId));
$btn6.addEventListener("click", () => sendTone("6", callId));
$btn7.addEventListener("click", () => sendTone("7", callId));
$btn8.addEventListener("click", () => sendTone("8", callId));
$btn9.addEventListener("click", () => sendTone("9", callId));
$btn10.addEventListener("click", () => sendTone("*", callId));
$btn0.addEventListener("click", () => sendTone("0", callId));
$btn12.addEventListener("click", () => sendTone("#", callId));
