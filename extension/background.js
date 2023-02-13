
console.log("Background script running");

//Create an array
var cache = [];

function makeRequest(domain){
  const request = new XMLHttpRequest();
  request.open('GET', 'http://localhost:8080/index.html?d='+domain, false);
  request.send(null);

  if (request.status === 200) {
    console.log(request.responseText);
    return request.responseText
  }

}

function cancel(requestDetails) {

  console.log("Intercept : " + requestDetails.url);
  let domain = (new URL(requestDetails.url));

  domain = domain.hostname.replace('www.','');
  console.log("Domain :" + domain); 
  if(domain=="localhost"){
    console.log('localhost mathed: ignoring');
    return {cancel:false};
  }

  var loadLocalStorage = localStorage.getItem("WhiteList");
  if(loadLocalStorage==null){
    loadLocalStorage="";
  }

  var ArrayList = loadLocalStorage.split(",");
  if(ArrayList.indexOf(domain) > -1){

    console.log("Whitelisted : "+domain);
    return {cancel: false};
  }

  if (cache.indexOf(domain) > -1) {
    console.log("Already in cache");
    return {cancel: false};
  }

  //makeRequest(domain);
  console.log("MakeRequest to "+domain);
  answer=makeRequest(domain);
  if(answer==0){
    console.log('Good for '+domain);
    cache.push(domain);
    //console.log(cache)
    return {cancel:false};
  }
  browser.tabs.create({
    url: "stop.html?site="+domain+"&url="+requestDetails.url,
  });
  console.log("Not good for "+domain);
  return{cancel:true};
  
} 


browser.webRequest.onBeforeRequest.addListener(
  cancel,
  {urls: ["*://*/*"]},
  ["blocking"]
);

