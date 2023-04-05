/* eslint-disable @typescript-eslint/no-var-requires */
// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process unless
// nodeIntegration is set to true in webPreferences.
// Use preload.js to selectively enable features
// needed in the renderer process.
const axios = require("axios");

const token =
  "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJpYXQiOjE2ODA3MzY5NjcsImV4cCI6MTY4MjAzMjk2NywianRpIjoiUUFoMHZFc29KUUZQIiwiYXBwbGljYXRpb25faWQiOiJhYjIyMmY3Zi1kYzQyLTQwOTQtYTUzOS03ZDQxNzEwNGM5MjciLCJzdWIiOiIiLCJhY2wiOiIifQ.Ys90yVvA37ZBk8QP3rk9x6wEulRW2Hs16OVWlKp0KqxTr7dcMBn8lHJ9r-eo52bROoNyoua97YUibBvcY6QVr5z-HGFogIUw3aV5jCurcfcXKjfkRwegJuz0pyOXNtrqaO3uvgsOabBSwFwYTBMDc1djNlp19SgBvrRu7OHz33ftuRzO2Ygo0qZvjw9RVqSAydAkpDwBa4tsa3eCajaZppC2UmDn3QUOxusC67AFllxyPaSi8jocCx6eJyvqM_dzVsYtT5iwEjPo64mKvqFcQk3R4Kk2p_ns4AhzqDj5ZfOsq2ZK2nlAPH1K4K8UJU9HZAQlh4FeNN_I1cQ-cT45IQ";

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
