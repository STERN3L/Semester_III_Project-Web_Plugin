
let header = document.getElementById("main_text");

let [domain, urllink] = getURLParams();

header.innerHTML = domain;

let phishing = document.getElementById("phishing_url");

phishing.addEventListener("click", function(){

        var currentstorage = localStorage.getItem("WhiteList");

        if (currentstorage == null) {
            currentstorage = "";
        } else {
            currentstorage = currentstorage + "," + domain;
        }
        localStorage.setItem("WhiteList", currentstorage);
        redirect(urllink);
    });


function redirect(urllink){
    chrome.tabs.getCurrent(function(tab) {
        chrome.tabs.update(tab.id, {url: urllink});
    });
}



let CloseTabId= document.getElementById("close_tab");
CloseTabId.addEventListener("click", function() {
    chrome.tabs.getCurrent(function(tab) {
        chrome.tabs.remove(tab.id);
    });
});

function getURLParams() {
    let url = new URL(window.location.href);
    let params = url.searchParams;
    let domain = params.get("site");

    let urllink = params.get("url");
    return [domain, urllink];
}

