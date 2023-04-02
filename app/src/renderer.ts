// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process unless
// nodeIntegration is set to true in webPreferences.
// Use preload.js to selectively enable features
// needed in the renderer process.
const accountSid = "";
const authToken = "";
// eslint-disable-next-line @typescript-eslint/no-var-requires
const client = window.require("twilio")(accountSid, authToken);

const callPhoneButton = document.getElementById("call-phone-button");

callPhoneButton.addEventListener("click", () => {
  // start a call to phone
  client.calls
    .create({
      url: "http://demo.twilio.com/docs/voice.xml",
      to: "",
      from: "",
    })
    .then((call: { sid: any }) => console.log(call.sid));
});
