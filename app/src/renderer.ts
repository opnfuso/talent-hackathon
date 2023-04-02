// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process unless
// nodeIntegration is set to true in webPreferences.
// Use preload.js to selectively enable features
// needed in the renderer process.
import { CallClient, CallAgent } from "@azure/communication-calling";
import { AzureCommunicationTokenCredential } from "@azure/communication-common";

let call;
let callAgent;

const calleePhoneInput = document.getElementById("callee-phone-input");
const callPhoneButton = document.getElementById("call-phone-button");
const hangUpPhoneButton = document.getElementById("hang-up-phone-button");

async function init() {
  const callClient = new CallClient();
  const tokenCredential = new AzureCommunicationTokenCredential(
    "<USER ACCESS TOKEN with VoIP scope>"
  );
  callAgent = await callClient.createCallAgent(tokenCredential);
  //callPhoneButton.disabled = false;
}

init();
