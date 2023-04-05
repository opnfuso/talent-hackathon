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
