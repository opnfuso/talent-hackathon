/* eslint-disable @typescript-eslint/no-var-requires */
// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process unless
// nodeIntegration is set to true in webPreferences.
// Use preload.js to selectively enable features
// needed in the renderer process.
const { Vonage } = require("@vonage/server-sdk");
const { NCCOBuilder, Stream, OutboundCallWithNCCO } = require("@vonage/voice");

const vonage = new Vonage({
  apiKey: "6b9e06a9",
  apiSecret: "kNPNBIl7UuPKbppC",
  applicationId: "ab222f7f-dc42-4094-a539-7d417104c927",
  privateKey: "../private.key",
});

async function makeCall() {
  const builder = new NCCOBuilder();
  builder.addAction(
    new Stream(
      "https://github.com/anars/blank-audio/blob/master/1-hour-and-20-minutes-of-silence.mp3?raw=true",
      -1,
      false,
      0
    )
  );
  const resp = await vonage.voice.createOutboundCall(
    new OutboundCallWithNCCO(builder.build(), {
      number: "5213320683941 ",
      type: "phone",
    })
  );

  console.log(resp);
}

const $callBtn = document.getElementById;
