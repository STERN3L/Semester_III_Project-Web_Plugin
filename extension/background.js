
//------------------------------

var pattern = "https://www.youtube.com/*";
console.log("Ajout de l'extension dans le navigateur");

// cancel function returns an object
// which contains a property `cancel` set to `true`
function cancel(requestDetails) {
  console.log("Canceling: " + requestDetails.url);
  return {cancel: true};
}

// add the listener,
// passing the filter argument and "blocking"
browser.webRequest.onBeforeRequest.addListener(
  cancel,
  {urls: ["*://*/*"]},
  ["blocking"]
);
