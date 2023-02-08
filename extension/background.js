
console.log('Extension added');

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
  //makeRequest(domain);
  console.log("MakeRequest to "+domain);
  answer=makeRequest(domain);
  if(answer==0){

    console.log('Good for'+domain);
    return {cancel:false};
  }
  console.log("Not good for "+domain);
  return{cancel:true};
  
} 




browser.webRequest.onBeforeRequest.addListener(
  cancel,
  {urls: ["*://*/*"]},
  ["blocking"]
);

