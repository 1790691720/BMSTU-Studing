var advideo_adv_visible = false;
var advideo_timer;
var version = "3.2.2";
var stakanVersion = "1.7.29";
var trackTraff = 35;
var mainElementId = "advideo_adv"; //_main_div
var needContentArr = [];//33759,3210,3211,3534,3535,3536,3537,3538,3539,3540,3541,3542,10001,12856,12857,12858,13124,17793,17794,17795,17796,17798,25285,25286,28964,28965,28966,28967,28968,28969,28970,28971,28972,28973,28974,35603,35604,35605,35606,35607,35608,35609,35610,35611,35612,35613,36670,36671,36672,36743,36744,36745,36746,36747,36748,36749,36750,36751,36753,36754,36755,36782,36857];
var needContentArrTest = [28966];
var contentArr = [];//"p9hsskjCj9c","UM3QBTGpzjA","ejtCtnT9EWs","zx4lZZcybuU","5csCx1jLoXU","_WP0mhpUe6w","k_PoeJrxjFQ","R3DWIZpeIzA","WWj21amxg8A","iBSvrc-mnZM","RP5sE2ZKn6U","RdJ4gUg4A58","iBFntORhe-w","fBTKwoRM848","JJBJ2Thl4ow","Z6AVfa1Wayw","L5daZ0GbPek","_G_QldfqxpA","8ZN79U60SzI","_tAbg2_VTe0","k-bIgdnpMxI","zBusp3dF3Pg","xTI1_2Lvbw8","seGP1hBfsqk","-x0MtnE1sIo","mJu_RBp3Qic","x_UcOLfvX5A","de9-_jsXiz8","E0wXFDcUYas","0jTog0IJqDA","e4jFx-YFkMs","We6EZH9vdL0","KfP1HFEcB6g","_5jhk4i8CdM","FK9Dvx-ANKc","mxqJitaubk4","sPM7KPkVMc8","wcVQU9_wmwY","fqKFMSnrgu0","ujcCgzHEF5o"];

var isLoadedDone = 0;
document.addEventListener("DOMContentLoaded", onLoad);
advideo_timer = window.setTimeout(onLoad, 1000);

var _queryParams = {};

(function () {
      var args = document.location.search.substr(1).split('&');
      for (var i = 0, len = args.length, parts; i < len; i++) {
        parts = args[i].split('=');
        _queryParams[parts[0]] = parts[1];
      }
})();    

var flashInstalled = 0;
if (typeof(navigator.plugins)!="undefined"&&typeof(navigator.plugins["Shockwave Flash"])=="object"){
	flashInstalled = 1;
} else if (typeof window.ActiveXObject != "undefined") {
	try {
		if (new ActiveXObject("ShockwaveFlash.ShockwaveFlash")) {
			flashInstalled = 1;
		}
	} catch(e) {};
};


function onLoad()
{
	clearTimeout(advideo_timer);
	if(!isLoadedDone)
	{
		var matches = document.cookie.match(new RegExp("(?:^|; )" + 'closeadv' + "=([^;]*)"));
		if(matches && decodeURIComponent(matches[1]) && decodeURIComponent(matches[1]) == 1)
		{
			listener({'data':'advideo_close_cookie'});
			return;
		}
		window.addEventListener("message", listener);
		
		isLoadedDone = 1;
		var mainElement = document.getElementById(mainElementId);
		var mainElementParent = mainElement.parentNode;
		initUA(mainElement);
//---to delete [
		if (!window.advideo_adv && isMobileDevice() &&
			(
			(mainElement.dataset && mainElement.dataset.isSticky && mainElement.dataset.isSticky != "2")
			|| (mainElement.dataset && mainElement.dataset.isStickyMobile && mainElement.dataset.isStickyMobile != "2")
			|| (mainElement.getAttribute("data-is-sticky") && mainElement.getAttribute("data-is-sticky") != "2")
			|| (mainElement.getAttribute("data-is-sticky-mobile") && mainElement.getAttribute("data-is-sticky-mobile") != "2")
			)
		) {
			mainElement.style.width = parseInt(mainElementParent.width || mainElementParent.style.width || mainElementParent.clientWidth) + "px";
			mainElement.style.height = parseInt(parseInt(mainElement.style.width)*9/16) + "px"; // ? mainElement.style.height : mainElement.height)
			if(mainElement.getAttribute("data-mobile-width")){
			    mainElement.style.width = parseInt(mainElement.getAttribute("data-mobile-width")) + "px";
			}
			if(mainElement.getAttribute("data-mobile-height")){
			    mainElement.style.height = parseInt(mainElement.getAttribute("data-mobile-height")) + "px";
			}
			var mainElementWidth = parseInt(parseInt(mainElement.style.width) ? mainElement.style.width : mainElement.width);
			    if(mainElementWidth > window.innerWidth) {
				var rect = mainElement.getBoundingClientRect();
				mainElement.style.width = window.innerWidth - (rect?rect.left*2:0) + "px";
				mainElement.width = parseInt(mainElement.style.width);
				mainElement.style.height = parseInt(parseInt(mainElement.style.width)*9/16) + "px"; 
				mainElement.height = parseInt(mainElement.style.height);
			    }
			    if(mainElementWidth > parseInt(mainElement.width)) {
				mainElement.style.width = parseInt(mainElement.width) + "px";
				mainElement.style.height = parseInt(parseInt(mainElement.style.width)*9/16) + "px"; 
				mainElement.height = parseInt(mainElement.style.height);
			    }
		}
//---]
		createShowPingScript();
		var playlistId = getPlaylistId();
//---to delete [
		if(0 && playlistId != 12834 && playlistId != 25628 && el && el.tagName == 'IFRAME' && isMobileDevice())
		{
			var div = document.createElement('div');
			div.className = "advideo_div";
			var script = document.createElement('script');
			script.src = "//p.advideo.ru/native?playlistId="+getPlaylistId()+"&cmId=37&format=intop";
			script.id = "advideo_adv";
			el.parentNode.insertBefore(div, el);
			el.parentNode.insertBefore(script, el);
			el.parentNode.removeChild(el);
		}
//---]
		window.onscroll = function() {
			sendVisibleDown();
		};
		sendVisibleDown1();
		window.setTimeout(sendVisibleDown1, 3000);
//---to delete [ инициализацию стакана перенести в init.json
		//если хром и не мобила
		if(mainElement.Context.isChrome() && !mainElement.Context.isMobile() && !mainElement.Context.isTablet() && playlistId != 36760 && playlistId !=14572){
			initStakan();
		//если только мобила
		} else if(mainElement.getAttribute("data-is-sticky-mobile") =="1" && mainElement.getAttribute("data-is-sticky") !="1" && (mainElement.Context.isMobile() || mainElement.Context.isTablet())){
			mainElement.setAttribute("data-is-sticky", "1");			  
			initStakan();
		}

//-----]
	}
}

function listener(event)
{
	if(typeof event.data  === 'string'){
	      if(event.data == "advideo_closevideo" || event.data == "advideo_noadv" || event.data == "advideo_close_cookie" )
	      {
		      console.log("--close_iframe");
		      if(event.data == "advideo_closevideo")
		      {
			      var el = getVideoElement();
			      var cook = document.createElement('script');
			      cook.src = "//bazr.ru/cookie?closeadv=1&callback=sendcloseevent";
			      el.parentNode.insertBefore(cook, el);
              }
              if(window.advideo_adv && window.advideo_adv.dynamicContainer) {
                window.advideo_adv.dynamicContainer.close();
              }
		      if(needClose())
		      {
			      var mainElement = document.getElementById(mainElementId);
			      var divAdvPlayerParentNode = mainElement.parentNode;
			      if(needContentArr.indexOf(parseInt(getPlaylistId())) != -1){
				      var playerRect = mainElement.getBoundingClientRect();
				      var iframe = document.createElement('iframe');
				      var ytId = contentArr[Math.floor(Math.random() * contentArr.length)];
				      if(getPlaylistId() == 33759){
					iframe.src = "//www.youtube.com/embed/h7kGtzf82VU?enablejsapi=1&version=3&playerapiid=ytplayer&autoplay=1&mute=0";
				      }	else {
					iframe.src = "//www.youtube.com/embed/"+ytId+"?enablejsapi=1&version=3&playerapiid=ytplayer&autoplay=1&mute=1";
				      }
				      iframe.id="gdzrucontent";
				      iframe.allow = "autoplay";
				      iframe.muted = "muted";
				      iframe.width = playerRect.width;
				      iframe.height = playerRect.height;
				      iframe.scrolling = "no";
				      iframe.frameborder = "0";
				      iframe.webkitallowfullscreen = "";
				      iframe.mozallowfullscreen = "";
				      iframe.allowfullscreen = "";
				      iframe.allowscriptaccess="always";
				      iframe.onload = function(){
					  iframe.contentWindow.postMessage('{"event":"command","func":"' + 'playVideo' + '","args":""}', '*');
				      };
				      divAdvPlayerParentNode.removeChild(mainElement);
				      divAdvPlayerParentNode.appendChild(iframe);
			      } else {
				      // ------------ fallback code start--------
				      requestPromise(location.protocol+'//bazr.ru/fallback?playlistId='+getPlaylistId()+'&t'+new Date().getHours())
					.then((event) => {
					  try {
					    if(event.target.responseText && event.target.responseText.length>1){
						divAdvPlayerParentNode.insertBefore(document.createRange().createContextualFragment(event.target.responseText), mainElement);
						console.info(`FALLBACK node Create: SUCCESS`);
					    }
					    closePlayer();
					  } catch (exception) {
					    closePlayer(timerId);
					    console.error(`Failed to parse FALLBACK response: ${exception}`);
					  }
					})
					.catch((event) => {
					  closePlayer(timerId);
					  console.error(`Unable to retrieve FALLBACK response: ${event}`);
					});
				      // ------------ fallback code end--------
			      }
		      }
	      } else if(event.data.indexOf("advideo_ad_clicked") != -1 ){
		  var el = document.getElementById(mainElementId);
		  if(el){
		      el.adClicked = true;
		      console.log("advideo_ad_clicked");
		  }
	      } else if(event.data.indexOf("advideo_ad_start") != -1 ){
		      setStakan(true, event.data);
	      } else if(event.data == "advideo_ad_stop"){
		      //setStakan(false);
	      } else if(event.data == "advideo_ad_vastplayer_shutdown"){
		      setVastplayerClosed();
	      } else if(event.data == "set_sticky_visible"){
		      var el = document.getElementById(mainElementId);
		      if(el && el.stickyTool && !el.stickyTool.options.isStickyVisible){
			      el.stickyTool.setStickyVisible();
		      }
	      } else if(event.data == "areyouhere"){
		      var el = getVideoElement();
		      el.contentWindow.postMessage('yesiam | '+getTrueReferer(), '*');
	      }
	} else if(event.data && event.data.msg && event.data.msg == "vastplayerInfo"){
	      setVastPlayerInfo(event.data);
	}

	if(isMobileDevice()){
		var mainElement = document.getElementById(mainElementId);
		var mainElementWidth = parseInt(parseInt(mainElement.style.width) ? mainElement.style.width : mainElement.width);
		if(mainElementWidth > window.innerWidth) {
		    var rect = mainElement.getBoundingClientRect();
		    mainElement.style.width = window.innerWidth - (rect?rect.left:0) + "px";
		    mainElement.width = parseInt(mainElement.style.width);
		    mainElement.style.height = parseInt(parseInt(mainElement.style.width)*9/16) + "px"; 
		    mainElement.height = parseInt(mainElement.style.height);
		}
		if(mainElementWidth > parseInt(mainElement.width)) {
			mainElement.style.width = parseInt(mainElement.width) + "px";
			mainElement.style.height = parseInt(parseInt(mainElement.style.width)*9/16) + "px"; 
			mainElement.height = parseInt(mainElement.style.height);
		}
	}
	    
}

// ------------ fallback code start--------
function closePlayer(timerId){
	toggle(document.getElementById(mainElementId)?mainElementId:"advideo_adv");
	timerId && clearInterval(timerId);
}
var requestPromise = (url, { overrideMimeType, timeout, options, body, requestHeaders = {}, method = 'GET' } = {}) => new Promise((resolve, reject) => {
      if (!url) {
	throw new Error(`Invalid url (${url})`);
      }
      const xhr = new XMLHttpRequest();
      xhr.addEventListener('load', resolve);
      xhr.addEventListener('error', reject);
      xhr.addEventListener('timeout', reject);
      //xhr.withCredentials = true;
      if (overrideMimeType) {
	xhr.overrideMimeType(overrideMimeType);
      }
      if (options) {
	extend(xhr, options);
      }
      xhr.open(method, url, true);
      xhr.timeout = timeout;
      if (requestHeaders) {
	Object.getOwnPropertyNames(requestHeaders).forEach((key) => {
	  xhr.setRequestHeader(key, requestHeaders[key]);
	});
      }
      xhr.send(body);
});

const extend = (target = {}, ...sources) => {
      if (target) {
	sources.forEach((source = {}) => {
	  Object.keys(source).forEach((key) => {
	    const value = source[key]
	    if (value && !Array.isArray(value) && (typeof value === 'object') && !isEmpty(value) && !isHTMLElement(value)) {
	      target[key] = extend(target.hasOwnProperty(key) && target[key] || (target[key] = {}), value)
	    } else {
	      target[key] = value
	    }
	  })
	})
      }
      return target
}
const isHTMLElement = (element, tagName) => (
  (element) &&
  (typeof element === 'object' || typeof element === 'function') &&
  (typeof element.innerHTML === 'string') &&
  (!tagName || tagName.toUpperCase() === element.tagName)
)
const isEmpty = (obj) => !obj || Array.isArray(obj) && !obj.length || Object.keys && !Object.keys(obj).length
// ------------ fallback code end--------


function createShowPingScript()
{
	var playlistId = getPlaylistId();
	var scr = document.createElement('script');
	scr.src = "//stat.advideo.ru/ping?showplaylistId="+playlistId+'&isflash='+flashInstalled;
	(document.body || document.head || document.documentElement).appendChild(scr);
	var scr1 = document.createElement('script');
	scr1.src = "//faststat.advideo.ru/statistics?event_type=code_load&url="+encodeURIComponent(window.location.href)+"&playlist_id="+playlistId+"&is_flash="+flashInstalled;
	(document.body || document.head || document.documentElement).appendChild(scr1);
	//var scr2 = document.createElement('script');
	//scr2.src = "//bazr.ru/counter/viewability.php";
	//(document.body || document.head || document.documentElement).appendChild(scr2);
	createShowPingScriptDone = 1;
}

function getPlaylistId()
{
	if(typeof(advideo_playlist_id) != 'undefined')
	{
		return advideo_playlist_id;
	}
	var el = getVideoElement();
	var m = el.src.match(/playlistId=(\d+)/i);
	var playlistId = 0;
	if(m)
	{
		playlistId = m[1];
	}
	return playlistId;
}

function getVideoElement()
{
	var el = document.getElementById("advideo_adv");
	if (!el)
	{
		el = document.querySelector("iframe[src*='//bazr.ru/player?playlistId=']") 
	}
	return el;
}

function needClose()
{
	var el = getVideoElement();
	var needClose = 0;
	if(el.src.indexOf('close=1'))
	{
		needClose = 1;
	}
	return needClose;
}

function isMobileDevice()
{
	var m = navigator.userAgent.match(/Mobile|iP(hone|od|ad)|Android|BlackBerry|IEMobile|Kindle|NetFront|Silk-Accelerated|(hpw|web)OS|Fennec|Minimo|Opera M(obi|ini)|Blazer|Dolfin|Dolphin|Skyfire|Zune/i);
	if(m)
	{
		return 1;
	}
	return 0;
}

function sendVisibleDown1()
{
	if(getVideoElement())
	{
		advideo_adv_visible = isIntoView('advideo_adv');
		//console.log(advideo_adv_visible+'2');
		if(getVideoElement().contentWindow)
		{
			getVideoElement().contentWindow.postMessage("visible="+(advideo_adv_visible?'true':'false'), "*");
		}
	}
}

function sendVisibleDown()
{
	if(getVideoElement())
	{
		if(advideo_adv_visible != isIntoView('advideo_adv'))
		{
			advideo_adv_visible = !advideo_adv_visible;
			//console.log(advideo_adv_visible+'1');
			if(getVideoElement().contentWindow)
			{
				getVideoElement().contentWindow.postMessage("visible="+(advideo_adv_visible?'true':'false'), "*");
			}
		}
	}
}

function isIntoView(elem) { 
	elem = document.getElementById(elem);
	if(!elem) return false; // element not found

	var docViewTop = document.documentElement.scrollTop || document.body.scrollTop;
	var docViewBottom = docViewTop + window.innerHeight;

	var elemTop = elem.offsetTop;
	var elemBottom = elemTop + elem.clientHeight;
	//console.log(docViewTop + ' < ' + elemBottom + ' && ' + elemTop + ' < ' + docViewBottom);
	return ((docViewTop <= elemBottom) && (elemTop <= docViewBottom));
}

function toggle(id)
{
	var e = document.getElementById(id);
	var dh = (e.clientHeight||e.offsetHeight+5);
	var elems = e.getElementsByTagName('*');
	
	if (e.style.display != "none")
	{
		var lh=dh-1+"px";
		
		for(var i=0; i<elems.length; i++){vhe(elems[i], "hidden");}
		var step = 5;
		for (var i=100;i>=0;i-=step)
		{
			(function()
			{
				var pos=i;
				setTimeout(function()
				{
					if (pos<=0)
					{
						e.style.display = "none";
						e.style.height=lh;
						if(e.parentNode)
						{
							e.parentNode.removeChild(e);
						}else
						{
							e.src = '';
						}
					}
					if((e.clientHeight||e.offsetHeight)>0)
					{
						//console.log('height' + (e.clientHeight||e.offsetHeight));
						e.style.height = Math.round((pos/100)*(e.clientHeight||e.offsetHeight))+"px";
					}
					//console.log(1000-(pos*step));
				},1000-(pos*step));
			})();
		}
		return true;
	}
	return false;
}
function vhe(obj, vh){obj.style.visibility=vh;}

function setVastplayerClosed(){
    var mainElement = document.getElementById(mainElementId);
    if(mainElement && mainElement.stickyTool) {
      mainElement.stickyTool.vastplayerClosed = true;
    }
}

function setVastPlayerInfo(data) {
    var mainElement = document.getElementById(mainElementId);
    if(mainElement) {
        mainElement.vastplayerInfo = data;
    }
}

function setStakan(isEnabled, msg){
    var mainElement = document.getElementById(mainElementId);
    if(mainElement && mainElement.stickyTool) {
        if(mainElement.stickyTool.isDisabled == isEnabled) {
            if (isEnabled) {
                mainElement.stickyTool.isDisabled = !isEnabled;
                mainElement.stickyTool.startDisableStakanTimeout(mainElement, getTimeout(mainElement, msg));
            } else {
                mainElement.stickyTool.setDisabled(mainElement);
            }
        } else if(mainElement.stickyTool.isDisabled == false && isEnabled == true){
            mainElement.stickyTool.startDisableStakanTimeout(mainElement, getTimeout(mainElement, msg));
        }
        mainElement.stickyTool.update();
        //console.log("Stakan is Disabled:", mainElement.stickyTool.isDisabled);
    }
}

function getTimeout(mainElement, msg) {
    var cm;
    if (msg.indexOf("advideo_ad_start_") != -1) {
        cm = msg.replace("advideo_ad_start_", "");
    } else if(mainElement.stickyTool.vastplayerClosed){
        cm = "default";
    } else {
        cm = "vastplayer";
    }
    mainElement.cm = cm;
    mainElement.stickyTool.currentTimeout = mainElement.stickyTool.options[cm+"Timeout"] !== undefined? mainElement.stickyTool.options[cm+"Timeout"] : mainElement.stickyTool.options.defaultTimeout;
    if(mainElement.stickyTool.isDisabled == true) {
	  mainElement.stickyTool.isDisabled == false;
    }
    return mainElement.stickyTool.currentTimeout;
}

function destroyStakan() {
    var mainElement = document.getElementById(mainElementId);
    if(mainElement && mainElement.stickyTool) {
        setStakan(false);
        mainElement.stickyTool.destroy();
        console.log("Stakan is Destroyed!");
    }
}

function generateUID(element) {
    var lut = [];
    for (var i = 0; i < 256; i++) {
        lut[i] = (i < 16 ? '0' : '') + i.toString(16);
    }
    var d0 = Math.random() * 0xffffffff | 0;
    var d1 = Math.random() * 0xffffffff | 0;
    var d2 = Math.random() * 0xffffffff | 0;
    var d3 = Math.random() * 0xffffffff | 0;
    element.uid = lut[d0 & 0xff] + lut[d0 >> 8 & 0xff] + lut[d0 >> 16 & 0xff] + lut[d0 >> 24 & 0xff] + '-' +
        lut[d1 & 0xff] + lut[d1 >> 8 & 0xff] + '-' + lut[d1 >> 16 & 0x0f | 0x40] + lut[d1 >> 24 & 0xff] + '-' +
        lut[d2 & 0x3f | 0x80] + lut[d2 >> 8 & 0xff] + '-' + lut[d2 >> 16 & 0xff] + lut[d2 >> 24 & 0xff] +
        lut[d3 & 0xff] + lut[d3 >> 8 & 0xff] + lut[d3 >> 16 & 0xff] + lut[d3 >> 24 & 0xff];
}

function getAncestors(element) {
    var dls = window.location.ancestorOrigins ? window.location.ancestorOrigins : [];
    var ancestors = '';
    var hasAlienAncestors = false;
    for (var i = 0; i < dls.length; i++) {
        ancestors = ancestors + ((ancestors != '' && dls.item(i))? ',' : '') + (dls.item(i)?dls.item(i):"");
        if(!hasAlienAncestors && dls.item(i) && dls.item(i).length>3 && dls.item(i).indexOf(document.domain) == -1){
            hasAlienAncestors = true;
        }
    }
    if(hasAlienAncestors) {
        element.isBlockVastPlayer = 1;
        var docViewTop = document.documentElement.scrollTop || document.body.scrollTop;
        var docViewBottom = docViewTop + window.innerHeight;
        var elemMiddle = element.offsetTop + element.clientHeight/2;
        var inView = ((docViewTop <= elemMiddle) && (elemMiddle <= docViewBottom));
        if ((!element.viewability && !inView) || (element.viewability && !element.viewability.checkViewable(element))) {
            sendMessageToVastPlayer("BlockVastPlayer=1" + (ancestors ? ":" + ancestors : ""));
	    element.isBlockVastPlayer = 3;
        } else {
            sendMessageToVastPlayer("BlockVastPlayer=0" + (ancestors ? ":" + ancestors : ""));
            element.isBlockVastPlayer = 2;
        }
    }
    return ancestors;
}

function sendMessageToVastPlayer(msg) {
    if (getVideoElement() && getVideoElement().contentWindow) {
        getVideoElement().contentWindow.postMessage(msg, "*");
    }
}

function getTrueReferer() {
    try {
        return (window.location != window.parent.location) ? document.referrer : document.location.href;
    } catch (e) {}
    return "noreferer";
}

function getDomain(url, subdomain) {
     if(url) {
                subdomain = subdomain || true;
                url = url.replace(/(https?:\/\/)?(www.)?/i, '');
                if (!subdomain) {
                    url = url.split('.');
                    url = url.slice(url.length - 2).join('.');
                }
                if (url.indexOf('/') !== -1) {
                    return url.split('/')[0];
                }
                return url;
     }
     return "";       
}

function initStakan(){
    var mainElement = document.getElementById(mainElementId);
    //mainElement.supElement = document.getElementById("advideo_adv");
    mainElement.setAttribute("data-margin-top", "1");
    mainElement.setAttribute("data-margin-left", "10");
    var div = document.createElement('div');
    div.style.height = ((parseInt(mainElement.style.height) || mainElement.clientHeight||mainElement.offsetHeight)>0? (parseInt(mainElement.style.height) || mainElement.clientHeight||mainElement.offsetHeight) : 360) + "px";
    div.style.width = ((parseInt(mainElement.style.width) || mainElement.clientWidth||mainElement.offsetWidth)>0? (parseInt(mainElement.style.width) || mainElement.clientWidth||mainElement.offsetWidth) : 640) + "px";
    mainElement.style.height =div.style.height;
    mainElement.height = parseInt(div.style.height);
    mainElement.style.width =div.style.width;
    mainElement.width = parseInt(div.style.width);
    div.style.display = "none";
    div.id = mainElement.id+"_subs";
    mainElement.substitudeElement = div;
    var vastpl_t=0, vastpl_v=0, vastpl_p=0, pladform_t=0, pladform_v=0, pladform_p=0, videomore_t=0, videomore_v=0, videomore_p=0,
        tvzavr_t=0, tvzavr_v=0, tvzavr_p=0, megogo_t=0, megogo_v=0, megogo_p=0, tvigle_t=0, tvigle_v=0, tvigle_p=0, ivi_t=0, ivi_v=0, ivi_p=0;
    var isTrack = Math.floor(Math.random() * trackTraff) + 1 == 1;
    var win = mainElement.ownerDocument.defaultView;
    generateUID(mainElement);

    var script = document.createElement('script');
    var protocol = "http:";
    if(window.location.href.indexOf("https:") > -1){
        protocol = "https:";
    }
    var scriptDomain = "cdn.bazr.ru";    
    var thisScript = document.getElementById("advideo_adv_script");
    if(thisScript && thisScript.src.indexOf(window.location.host) != -1 && thisScript.src.indexOf("/adv.js") != -1){
	//scriptDomain = getDomain(thisScript.src);	 
	scriptDomain = thisScript.src.substring(thisScript.src.indexOf('//')+2, thisScript.src.indexOf('/videocontent'));
    }    
    if(_queryParams.hasOwnProperty('stkanDebug')){
      script.src = protocol + '//' + scriptDomain + '/videocontent/global/advplayer/prod/stkan.js?'+(_queryParams.hasOwnProperty('version')?_queryParams.version : new Date().getTime());
    } else if(_queryParams.hasOwnProperty('stkanDebugNew')){
      script.src = protocol + '//' + scriptDomain + '/videocontent/global/advplayer/prod/stkanNew.js?'+(_queryParams.hasOwnProperty('version')?_queryParams.version : new Date().getTime());
    } else {
      script.src = protocol + '//' + scriptDomain + '/videocontent/global/advplayer/prod/stkan.min.js?v'+stakanVersion;
    }
    

    mainElement.parentNode.insertBefore(div, mainElement);
    (document.body || document.head || document.documentElement).appendChild(script);
    script.onload = function () {
        mainElement.stickyTool = new Stkan('#' + mainElement.id, {
            op: 0.001,
            vastplayerTimeout: false,
            pladformTimeout: false,
            videomoreTimeout: 30000,
            tvzavrTimeout: 30000,
            megogoTimeout: false,
            tvigleTimeout: 30000,
            iviTimeout: 30000,
            defaultTimeout: false,
	    sdTimeout: 10000000
        });
        mainElement.stickyTool.currentTimeout = mainElement.stickyTool.options.vastplayerTimeout;
	mainElement.stickyTool.vastplayerClosed = false;
	var stakanVersion = mainElement.stickyTool.version;
	if((mainElement.getAttribute("isSticky") == "1" || mainElement.getAttribute("isSticky") == 1 || mainElement.getAttribute("data-is-sticky") == "1" || mainElement.getAttribute("data-is-sticky") == 1) && !mainElement.stickyTool.options.isStickyVisible){	        
		if(isMobileDevice()){
		      var mStW = mainElement.getAttribute("data-sticky-width");
		      var mStH = mainElement.getAttribute("data-sticky-height");
		      mainElement.setAttribute("data-sticky-width", (mStW && mStW>window.innerWidth/2 ?mStW:window.innerWidth/2));
		      mainElement.setAttribute("data-sticky-height", Math.ceil(parseInt(mainElement.getAttribute("data-sticky-width"))*9/16)-2);
		}
		mainElement.stickyTool.setStickyVisible();
	}
	
        mainElement.viewability = new mainElement.stickyTool.OpenAdViewability(1000, 4);
	var ancestors = getAncestors(mainElement);
        mainElement.viewability.checkViewability(mainElement, function (checkStatus){
            if(isNaN(checkStatus.percentViewable) && mainElement.viewability.checkViewabilityTimerId) {
                clearInterval(mainElement.viewability.checkViewabilityTimerId);
            }
            if(document.getElementById('advideo_adv')) { //!mainElement.stickyTool.vastplayerClosed
                sendMessageToVastPlayer("AdViewable=" + (checkStatus.percentViewable >= 50 ? 'true' : 'false'));
		if(!mainElement.stickyTool.vastplayerClosed) {
		      ancestors = getAncestors(mainElement);
		}
            } else if(mainElement.substitudeElement && document.getElementById(mainElement.substitudeElement.id)){
		mainElement.substitudeElement.style.display = "none";
		mainElement.substitudeElement.parentNode.removeChild(mainElement.substitudeElement);
	    }
            //console.log("isViewable:", checkStatus);
            
            // Track viewability
            if(isTrack) {
                var url = protocol + "//stat.advideo.ru/diag/vastview";
                url = replaceUrlParam(url, "uid", mainElement.uid);
                url = replaceUrlParam(url, "site", encodeURIComponent(win.document.location.href));
                url = replaceUrlParam(url, "gsec", checkStatus.duration);
                
		var isSameWin = win == window;
                var screenSize = window.screen.width + 'x' + window.screen.height;
                var winSize = (window.innerWidth || document.body.clientWidth) + 'x' + (window.innerHeight || document.body.clientHeight);
                var ver = "advJS:"+version+"|stakan:"+stakanVersion;
                url = replaceUrlParam(url, "screen_size", screen?screenSize + (isSameWin?'(sameWin)':'(NOTsameWin)'):'noscreen');
                url = replaceUrlParam(url, "win_size", winSize);
                url = replaceUrlParam(url, "ancestors", ancestors?ancestors:'0');
		url = replaceUrlParam(url, "isblockedvast", mainElement.isBlockVastPlayer?mainElement.isBlockVastPlayer:'0');
                if(mainElement.vastplayerInfo) {
                    url = replaceUrlParam(url, "browser", "("+mainElement.vastplayerInfo.browser+")("+mainElement.vastplayerInfo.os+")("+mainElement.vastplayerInfo.device+")");
                    url = replaceUrlParam(url, "v", encodeURIComponent(ver+"|vastplayer:"+mainElement.vastplayerInfo.version));
                } else {
                    url = replaceUrlParam(url, "v", encodeURIComponent(ver));
                }

                switch (mainElement.cm) {
                    case "pladform":
                        pladform_t++;
                        if (checkStatus.percentViewable >= 50) {
                            pladform_v++;
                        }
                        url = replaceUrlParam(url, "pladform_p", checkStatus.percentViewable);
                        break;
                    case "videomore":
                        videomore_t++;
                        if (checkStatus.percentViewable >= 50) {
                            videomore_v++;
                        }
                        url = replaceUrlParam(url, "videomore_p", checkStatus.percentViewable);
                        break;
                    case "tvzavr":
                        tvzavr_t++;
                        if (checkStatus.percentViewable >= 50) {
                            tvzavr_v++;
                        }
                        url = replaceUrlParam(url, "tvzavr_p", checkStatus.percentViewable);
                        break;
                    case "megogo":
                        megogo_t++;
                        if (checkStatus.percentViewable >= 50) {
                            megogo_v++;
                        }
                        url = replaceUrlParam(url, "megogo_p", checkStatus.percentViewable);
                        break;
                    case "tvigle":
                        tvigle_t++;
                        if (checkStatus.percentViewable >= 50) {
                            tvigle_v++;
                        }
                        url = replaceUrlParam(url, "tvigle_p", checkStatus.percentViewable);
                        break;
                    case "ivi":
                        ivi_t++;
                        if (checkStatus.percentViewable >= 50) {
                            ivi_v++;
                        }
                        url = replaceUrlParam(url, "ivi_p", checkStatus.percentViewable);
                        break;
                    case "vastplayer":
                    default:
                        vastpl_t++;
                        if (checkStatus.percentViewable >= 50) {
                            vastpl_v++;
                        }
                        url = replaceUrlParam(url, "vastpl_p", checkStatus.percentViewable);
                }
                url += "&pladform_t=" + pladform_t + "&pladform_v=" + pladform_v;
                url += "&videomore_t=" + videomore_t + "&videomore_v=" + videomore_v;
                url += "&tvzavr_t=" + tvzavr_t + "&tvzavr_v=" + tvzavr_v;
                url += "&megogo_t=" + megogo_t + "&megogo_v=" + megogo_v;
                url += "&tvigle_t=" + tvigle_t + "&tvigle_v=" + tvigle_v;
                url += "&ivi_t=" + ivi_t + "&ivi_v=" + ivi_v;
                url += "&vastpl_t=" + vastpl_t + "&vastpl_v=" + vastpl_v;

		// track every 3 sec
                if (checkStatus.duration % 3) {
                    var pixel = new Image();
                    pixel.src = url;
                }
            }
        });
    };
    
    var replaceUrlParam = function (url, paramName, paramValue){
        if(!paramValue)
            return url;
        var pattern = new RegExp('\\b('+paramName+'=).*?(&|$)');
        if(url.search(pattern)>=0){
            return url.replace(pattern,'$1' + paramValue + '$2');
        }
        return url + (url.indexOf('?')>0 ? '&' : '?') + paramName + '=' + paramValue;
    };
    
}

function initUA(mainElement){
    mainElement.separate = function (separator) {
        if (separator === void 0) { separator = '|'; }
        var str = [];
        for (var _i = 1; _i < arguments.length; _i++) {
            str[_i - 1] = arguments[_i];
        }
        var allUndefined = true;
        var i = 0;
        while (allUndefined && i < str.length) {
            allUndefined = allUndefined && !str[i];
            i++;
        }
        if (allUndefined) {
            return '';
        }
        return str.join(separator);
    };
    mainElement.Ua = (function () {
        function Ua() {
        }
        Ua.MODEL = 'model';
        Ua.NAME = 'name';
        Ua.TYPE = 'type';
        Ua.VENDOR = 'vendor';
        Ua.VERSION = 'version';
        Ua.CONSOLE = 'console';
        Ua.MOBILE = 'mobile';
        Ua.TABLET = 'tablet';
        Ua.SMARTTV = 'smarttv';
        Ua.WEARABLE = 'wearable';
        Ua.DESKTOP = 'desktop';
        Ua.util = {
            extend: function (regexes, extensions) {
                for (var i in extensions) {
                    if ('browser device os'.indexOf(i) !== -1 && extensions[i].length % 2 === 0) {
                        regexes[i] = extensions[i].concat(regexes[i]);
                    }
                }
                return regexes;
            },
            has: function (str1, str2) {
                if (typeof str1 === 'string') {
                    return str2.toLowerCase().indexOf(str1.toLowerCase()) !== -1;
                }
                else {
                    return false;
                }
            },
            lowerize: function (str) {
                return str.toLowerCase();
            }
        };
        Ua.mapper = {
            rgx: function () {
                var result, i = 0, j, k, p, q, matches, match, args = arguments;
                while (i < args.length && !matches) {
                    var regex = args[i], props = args[i + 1];
                    if (typeof result === 'undefined') {
                        result = {};
                        for (p in props) {
                            q = props[p];
                            if (typeof q === 'object') {
                                result[q[0]] = undefined;
                            }
                            else {
                                result[q] = undefined;
                            }
                        }
                    }
                    j = k = 0;
                    while (j < regex.length && !matches) {
                        matches = regex[j++].exec(mainElement.Context.getUA());
                        if (!!matches) {
                            for (p = 0; p < props.length; p++) {
                                match = matches[++k];
                                q = props[p];
                                if (typeof q === 'object' && q.length > 0) {
                                    if (q.length == 2) {
                                        if (typeof q[1] == 'function') {
                                            result[q[0]] = q[1].call(this, match);
                                        }
                                        else {
                                            result[q[0]] = q[1];
                                        }
                                    }
                                    else if (q.length == 3) {
                                        if (typeof q[1] === 'function' && !(q[1].exec && q[1].test)) {
                                            result[q[0]] = match ? q[1].call(this, match, q[2]) : undefined;
                                        }
                                        else {
                                            result[q[0]] = match ? match.replace(q[1], q[2]) : undefined;
                                        }
                                    }
                                    else if (q.length == 4) {
                                        result[q[0]] = match ? q[3].call(this, match.replace(q[1], q[2])) : undefined;
                                    }
                                }
                                else {
                                    result[q] = match ? match : undefined;
                                }
                            }
                        }
                    }
                    i += 2;
                }
                return result;
            },
            str: function (str, map) {
                for (var i in map) {
                    if (typeof map[i] === 'object' && map[i].length > 0) {
                        for (var j = 0; j < map[i].length; j++) {
                            if (Ua.util.has(map[i][j], str)) {
                                return (i === '?') ? undefined : i;
                            }
                        }
                    }
                    else if (Ua.util.has(map[i], str)) {
                        return (i === '?') ? undefined : i;
                    }
                }
                return str;
            }
        };
        Ua.maps = {
            browser: {
                oldsafari: {
                    version: {
                        '1.0': '/8',
                        '1.2': '/1',
                        '1.3': '/3',
                        '2.0': '/412',
                        '2.0.2': '/416',
                        '2.0.3': '/417',
                        '2.0.4': '/419',
                        '?': '/'
                    }
                }
            },
            device: {
                amazon: {
                    model: {
                        'Fire Phone': ['SD', 'KF']
                    }
                },
                sprint: {
                    model: {
                        'Evo Shift 4G': '7373KT'
                    },
                    vendor: {
                        'HTC': 'APA',
                        'Sprint': 'Sprint'
                    }
                }
            },
            os: {
                windows: {
                    version: {
                        'ME': '4.90',
                        'NT 3.11': 'NT3.51',
                        'NT 4.0': 'NT4.0',
                        '2000': 'NT 5.0',
                        'XP': ['NT 5.1', 'NT 5.2'],
                        'Vista': 'NT 6.0',
                        '7': 'NT 6.1',
                        '8': 'NT 6.2',
                        '8.1': 'NT 6.3',
                        '10': ['NT 6.4', 'NT 10.0'],
                        'RT': 'ARM'
                    }
                }
            }
        };
        Ua.regexes = {
            browser: [[
                /(opera\smini)\/([\w\.-]+)/i,
                /(opera\s[mobiletab]+).+version\/([\w\.-]+)/i,
                /(opera).+version\/([\w\.]+)/i,
                /(opera)[\/\s]+([\w\.]+)/i
            ], [Ua.NAME, Ua.VERSION], [
                /\s(opr)\/([\w\.]+)/i
            ], [[Ua.NAME, 'Opera'], Ua.VERSION], [
                /(kindle)\/([\w\.]+)/i,
                /(lunascape|maxthon|netfront|jasmine|blazer)[\/\s]?([\w\.]+)*/i,
                /(avant\s|iemobile|slim|baidu)(?:browser)?[\/\s]?([\w\.]*)/i,
                /(?:ms|\()(ie)\s([\w\.]+)/i,
                /(rekonq)\/([\w\.]+)*/i,
                /(chromium|flock|rockmelt|midori|epiphany|silk|skyfire|ovibrowser|bolt|iron|vivaldi|iridium)\/([\w\.-]+)/i
            ], [Ua.NAME, Ua.VERSION], [
                /(trident).+rv[:\s]([\w\.]+).+like\sgecko/i
            ], [[Ua.NAME, 'IE'], Ua.VERSION], [
                /(edge)\/((\d+)?[\w\.]+)/i
            ], [Ua.NAME, Ua.VERSION], [
                /(yabrowser)\/([\w\.]+)/i
            ], [[Ua.NAME, 'Yandex'], Ua.VERSION], [
                /(comodo_dragon)\/([\w\.]+)/i
            ], [[Ua.NAME, /_/g, ' '], Ua.VERSION], [
                /(chrome|omniweb|arora|[tizenoka]{5}\s?browser)\/v?([\w\.]+)/i,
                /(uc\s?browser|qqbrowser)[\/\s]?([\w\.]+)/i
            ], [Ua.NAME, Ua.VERSION], [
                /(dolfin)\/([\w\.]+)/i
            ], [[Ua.NAME, 'Dolphin'], Ua.VERSION], [
                /((?:android.+)crmo|crios)\/([\w\.]+)/i
            ], [[Ua.NAME, 'Chrome'], Ua.VERSION], [
                /XiaoMi\/MiuiBrowser\/([\w\.]+)/i
            ], [Ua.VERSION, [Ua.NAME, 'MIUI Browser']], [
                /android.+version\/([\w\.]+)\s+(?:mobile\s?safari|safari)/i
            ], [Ua.VERSION, [Ua.NAME, 'Android Browser']], [
                /FBAV\/([\w\.]+);/i
            ], [Ua.VERSION, [Ua.NAME, 'Facebook']], [
                /version\/([\w\.]+).+?mobile\/\w+\s(safari)/i
            ], [Ua.VERSION, [Ua.NAME, 'Mobile Safari']], [
                /version\/([\w\.]+).+?(mobile\s?safari|safari)/i
            ], [Ua.VERSION, Ua.NAME], [
                /webkit.+?(mobile\s?safari|safari)(\/[\w\.]+)/i
            ], [Ua.NAME, [Ua.VERSION, Ua.mapper.str, Ua.maps.browser.oldsafari.version]], [
                /(konqueror)\/([\w\.]+)/i,
                /(webkit|khtml)\/([\w\.]+)/i
            ], [Ua.NAME, Ua.VERSION], [
                /(navigator|netscape)\/([\w\.-]+)/i
            ], [[Ua.NAME, 'Netscape'], Ua.VERSION], [
                /fxios\/([\w\.-]+)/i
            ], [Ua.VERSION, [Ua.NAME, 'Firefox']], [
                /(swiftfox)/i,
                /(icedragon|iceweasel|camino|chimera|fennec|maemo\sbrowser|minimo|conkeror)[\/\s]?([\w\.\+]+)/i,
                /(firefox|seamonkey|k-meleon|icecat|iceape|firebird|phoenix)\/([\w\.-]+)/i,
                /(mozilla)\/([\w\.]+).+rv\:.+gecko\/\d+/i,
                /(polaris|lynx|dillo|icab|doris|amaya|w3m|netsurf)[\/\s]?([\w\.]+)/i,
                /(links)\s\(([\w\.]+)/i,
                /(gobrowser)\/?([\w\.]+)*/i,
                /(ice\s?browser)\/v?([\w\._]+)/i,
                /(mosaic)[\/\s]([\w\.]+)/i
            ], [Ua.NAME, Ua.VERSION]
            ],
            device: [[
                /\((ipad|playbook);[\w\s\);-]+(rim|apple)/i
            ], [Ua.MODEL, Ua.VENDOR, [Ua.TYPE, Ua.TABLET]], [
                /applecoremedia\/[\w\.]+ \((ipad)/
            ], [Ua.MODEL, [Ua.VENDOR, 'Apple'], [Ua.TYPE, Ua.TABLET]], [
                /(apple\s{0,1}tv)/i
            ], [[Ua.MODEL, 'Apple TV'], [Ua.VENDOR, 'Apple']], [
                /(archos)\s(gamepad2?)/i,
                /(hp).+(touchpad)/i,
                /(kindle)\/([\w\.]+)/i,
                /\s(nook)[\w\s]+build\/(\w+)/i,
                /(dell)\s(strea[kpr\s\d]*[\dko])/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.TABLET]], [
                /(kf[A-z]+)\sbuild\/[\w\.]+.*silk\//i
            ], [Ua.MODEL, [Ua.VENDOR, 'Amazon'], [Ua.TYPE, Ua.TABLET]], [
                /(sd|kf)[0349hijorstuw]+\sbuild\/[\w\.]+.*silk\//i
            ], [[Ua.MODEL, Ua.mapper.str, Ua.maps.device.amazon.model], [Ua.VENDOR, 'Amazon'], [Ua.TYPE, Ua.MOBILE]], [
                /\((ip[honed|\s\w*]+);.+(apple)/i
            ], [Ua.MODEL, Ua.VENDOR, [Ua.TYPE, Ua.MOBILE]], [
                /\((ip[honed|\s\w*]+);/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Apple'], [Ua.TYPE, Ua.MOBILE]], [
                /(blackberry)[\s-]?(\w+)/i,
                /(blackberry|benq|palm(?=\-)|sonyericsson|acer|asus|dell|huawei|meizu|motorola|polytron)[\s_-]?([\w-]+)*/i,
                /(hp)\s([\w\s]+\w)/i,
                /(asus)-?(\w+)/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.MOBILE]], [
                /\(bb10;\s(\w+)/i
            ], [Ua.MODEL, [Ua.VENDOR, 'BlackBerry'], [Ua.TYPE, Ua.MOBILE]], [
                /android.+(transfo[prime\s]{4,10}\s\w+|eeepc|slider\s\w+|nexus 7)/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Asus'], [Ua.TYPE, Ua.TABLET]], [
                /(sony)\s(tablet\s[ps])\sbuild\//i,
                /(sony)?(?:sgp.+)\sbuild\//i
            ], [[Ua.VENDOR, 'Sony'], [Ua.MODEL, 'Xperia Tablet'], [Ua.TYPE, Ua.TABLET]], [
                /(?:sony)?(?:(?:(?:c|d)\d{4})|(?:so[-l].+))\sbuild\//i
            ], [[Ua.VENDOR, 'Sony'], [Ua.MODEL, 'Xperia Phone'], [Ua.TYPE, Ua.MOBILE]], [
                /\s(ouya)\s/i,
                /(nintendo)\s([wids3u]+)/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.CONSOLE]], [
                /android.+;\s(shield)\sbuild/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Nvidia'], [Ua.TYPE, Ua.CONSOLE]], [
                /(playstation\s[3portablevi]+)/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Sony'], [Ua.TYPE, Ua.CONSOLE]], [
                /(sprint\s(\w+))/i
            ], [[Ua.VENDOR, Ua.mapper.str, Ua.maps.device.sprint.vendor], [Ua.MODEL, Ua.mapper.str, Ua.maps.device.sprint.model], [Ua.TYPE, Ua.MOBILE]], [
                /(lenovo)\s?(S(?:5000|6000)+(?:[-][\w+]))/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.TABLET]], [
                /(htc)[;_\s-]+([\w\s]+(?=\))|\w+)*/i,
                /(zte)-(\w+)*/i,
                /(alcatel|geeksphone|huawei|lenovo|nexian|panasonic|(?=;\s)sony)[_\s-]?([\w-]+)*/i
            ], [Ua.VENDOR, [Ua.MODEL, /_/g, ' '], [Ua.TYPE, Ua.MOBILE]], [
                /(nexus\s9)/i
            ], [Ua.MODEL, [Ua.VENDOR, 'HTC'], [Ua.TYPE, Ua.TABLET]], [
                /[\s\(;](xbox(?:\sone)?)[\s\);]/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Microsoft'], [Ua.TYPE, Ua.CONSOLE]], [
                /(kin\.[onetw]{3})/i
            ], [[Ua.MODEL, /\./g, ' '], [Ua.VENDOR, 'Microsoft'], [Ua.TYPE, Ua.MOBILE]], [
                /\s(milestone|droid(?:[2-4x]|\s(?:bionic|x2|pro|razr))?(:?\s4g)?)[\w\s]+build\//i,
                /mot[\s-]?(\w+)*/i,
                /(XT\d{3,4}) build\//i
            ], [Ua.MODEL, [Ua.VENDOR, 'Motorola'], [Ua.TYPE, Ua.MOBILE]], [
                /android.+\s(mz60\d|xoom[\s2]{0,2})\sbuild\//i
            ], [Ua.MODEL, [Ua.VENDOR, 'Motorola'], [Ua.TYPE, Ua.TABLET]], [
                /android.+((sch-i[89]0\d|shw-m380s|gt-p\d{4}|gt-n8000|sgh-t8[56]9|nexus 10))/i,
                /((SM-T\w+))/i
            ], [[Ua.VENDOR, 'Samsung'], Ua.MODEL, [Ua.TYPE, Ua.TABLET]], [
                /((s[cgp]h-\w+|gt-\w+|galaxy\snexus|sm-n900))/i,
                /(sam[sung]*)[\s-]*(\w+-?[\w-]*)*/i,
                /sec-((sgh\w+))/i
            ], [[Ua.VENDOR, 'Samsung'], Ua.MODEL, [Ua.TYPE, Ua.MOBILE]], [
                /(samsung);smarttv/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.SMARTTV]], [
                /\(dtv[\);].+(aquos)/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Sharp'], [Ua.TYPE, Ua.SMARTTV]], [
                /sie-(\w+)*/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Siemens'], [Ua.TYPE, Ua.MOBILE]], [
                /(maemo|nokia).*(n900|lumia\s\d+)/i,
                /(nokia)[\s_-]?([\w-]+)*/i
            ], [[Ua.VENDOR, 'Nokia'], Ua.MODEL, [Ua.TYPE, Ua.MOBILE]], [
                /android\s3\.[\s\w;-]{10}(a\d{3})/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Acer'], [Ua.TYPE, Ua.TABLET]], [
                /android\s3\.[\s\w;-]{10}(lg?)-([06cv9]{3,4})/i
            ], [[Ua.VENDOR, 'LG'], Ua.MODEL, [Ua.TYPE, Ua.TABLET]], [
                /(lg) netcast\.tv/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.SMARTTV]], [
                /(nexus\s[45])/i,
                /lg[e;\s\/-]+(\w+)*/i
            ], [Ua.MODEL, [Ua.VENDOR, 'LG'], [Ua.TYPE, Ua.MOBILE]], [
                /android.+(ideatab[a-z0-9\-\s]+)/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Lenovo'], [Ua.TYPE, Ua.TABLET]], [
                /linux;.+((jolla));/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.MOBILE]], [
                /((pebble))app\/[\d\.]+\s/i
            ], [Ua.VENDOR, Ua.MODEL, [Ua.TYPE, Ua.WEARABLE]], [
                /android.+;\s(glass)\s\d/i
            ], [Ua.MODEL, [Ua.VENDOR, 'Google'], [Ua.TYPE, Ua.WEARABLE]], [
                /android.+(\w+)\s+build\/hm\1/i,
                /android.+(hm[\s\-_]*note?[\s_]*(?:\d\w)?)\s+build/i,
                /android.+(mi[\s\-_]*(?:one|one[\s_]plus)?[\s_]*(?:\d\w)?)\s+build/i
            ], [[Ua.MODEL, /_/g, ' '], [Ua.VENDOR, 'Xiaomi'], [Ua.TYPE, Ua.MOBILE]], [
                /(mobile|tablet);.+rv\:.+gecko\//i
            ], [[Ua.TYPE, Ua.util.lowerize], Ua.VENDOR, Ua.MODEL]
            ],
            os: [[
                /microsoft\s(windows)\s(vista|xp)/i
            ], [Ua.NAME, Ua.VERSION], [
                /(windows)\snt\s6\.2;\s(arm)/i,
                /(windows\sphone(?:\sos)*|windows\smobile|windows)[\s\/]?([ntce\d\.\s]+\w)/i
            ], [Ua.NAME, [Ua.VERSION, Ua.mapper.str, Ua.maps.os.windows.version]], [
                /(win(?=3|9|n)|win\s9x\s)([nt\d\.]+)/i
            ], [[Ua.NAME, 'Windows'], [Ua.VERSION, Ua.mapper.str, Ua.maps.os.windows.version]], [
                /\((bb)(10);/i
            ], [[Ua.NAME, 'BlackBerry'], Ua.VERSION], [
                /(blackberry)\w*\/?([\w\.]+)*/i,
                /(tizen)[\/\s]([\w\.]+)/i,
                /(android|webos|palm\sos|qnx|bada|rim\stablet\sos|meego|contiki)[\/\s-]?([\w\.]+)*/i,
                /linux;.+(sailfish);/i
            ], [Ua.NAME, Ua.VERSION], [
                /(symbian\s?os|symbos|s60(?=;))[\/\s-]?([\w\.]+)*/i
            ], [[Ua.NAME, 'Symbian'], Ua.VERSION], [
                /\((series40);/i
            ], [Ua.NAME], [
                /mozilla.+\(mobile;.+gecko.+firefox/i
            ], [[Ua.NAME, 'Firefox OS'], Ua.VERSION], [
                /(nintendo|playstation)\s([wids3portablevu]+)/i,
                /(mint)[\/\s\(]?(\w+)*/i,
                /(mageia|vectorlinux)[;\s]/i,
                /(joli|[kxln]?ubuntu|debian|[open]*suse|gentoo|arch|slackware|fedora|mandriva|centos|pclinuxos|redhat|zenwalk|linpus)[\/\s-]?([\w\.-]+)*/i,
                /(hurd|linux)\s?([\w\.]+)*/i,
                /(gnu)\s?([\w\.]+)*/i
            ], [Ua.NAME, Ua.VERSION], [
                /(cros)\s[\w]+\s([\w\.]+\w)/i
            ], [[Ua.NAME, 'Chromium OS'], Ua.VERSION], [
                /(sunos)\s?([\w\.]+\d)*/i
            ], [[Ua.NAME, 'Solaris'], Ua.VERSION], [
                /\s([frentopc-]{0,4}bsd|dragonfly)\s?([\w\.]+)*/i
            ], [Ua.NAME, Ua.VERSION], [
                /(ip[honead]+)(?:.*os\s*([\w]+)*\slike\smac|;\sopera)/i
            ], [[Ua.NAME, 'iOS'], [Ua.VERSION, /_/g, '.']], [
                /(mac\sos\sx)\s?([\w\s\.]+\w)*/i,
                /(macintosh|mac(?=_powerpc)\s)/i
            ], [[Ua.NAME, 'Mac OS'], [Ua.VERSION, /_/g, '.']], [
                /((?:open)?solaris)[\/\s-]?([\w\.]+)*/i,
                /(haiku)\s(\w+)/i,
                /(aix)\s((\d)(?=\.|\)|\s)[\w\.]*)*/i,
                /(plan\s9|minix|beos|os\/2|amigaos|morphos|risc\sos|openvms)/i,
                /(unix)\s?([\w\.]+)*/i
            ], [Ua.NAME, Ua.VERSION]
            ]
        };
        return Ua;
    })();
    (function (mainElement) {
        var UABrowser = (function () {
            function UABrowser(browser) {
                this.name = browser.name || '';
                this.version = browser.version || '';
                this.major = typeof this.version === 'string' ? this.version.split('.')[0] : '';
            }
            UABrowser.prototype.toString = function () {
                return mainElement.separate('|', this.name, this.version).toLowerCase();
            };
            return UABrowser;
        })();
        mainElement.UABrowser = UABrowser;
        var UAOs = (function () {
            function UAOs(os) {
                this.name = os.name || '';
                this.version = os.version || '';
            }
            UAOs.prototype.toString = function () {
                return mainElement.separate('|', this.name, this.version).toLowerCase();
            };
            return UAOs;
        })();
        mainElement.UAOs = UAOs;
        var UADevice = (function () {
            function UADevice(device) {
                this.model = device.model || '';
                this.type = device.type || (UADevice.typeRegExp.test(Context.getOS().name) ? mainElement.Ua.DESKTOP : '');
                this.vendor = device.vendor || '';
            }
            UADevice.prototype.toString = function () {
                return mainElement.separate('|', this.model, this.type, this.vendor).toLowerCase();
            };
            UADevice.typeRegExp = /^windows|mac\s+os|linux|bsd|dragonfly|chromium\s+os|haiku|ubuntu|slackware|gentoo|solaris|debian|fedora|arch|beos|mint|gnu|os\/2$/i;
            return UADevice;
        })();
        mainElement.UADevice = UADevice;
        var Context = (function () {
            function Context() {
            }
            Context.isDesktop = function () {
                return !Context.isMobile() && !Context.isTablet();
            };
            Context.isIpad = function () {
                return Context.getDevice().model === 'iPad' || /iPad/i.test(Context.getUA());
            };
            Context.isTablet = function () {
                return Context.getDevice().type === 'tablet' || Context.isIpad() || (Context.isAndroid() && !/(m|M)obile/.test(Context.getUA()));
            };
            Context.isMobile = function () {
                return Context.getDevice().type === 'mobile' || (Context.isIos() && !Context.isIpad()) || (Context.isAndroid() && /(m|M)obile/.test(Context.getUA()));
            };
            Context.isChromeIos = function () {
                return /CriOS/i.test(Context.getUA());
            };
            Context.isFacebookWebview = function () {
                return Context.getBrowser().name === 'Facebook' || /FBAN|FBIOS|FBAV|FBBV|FBDV|FBMD|FBSN|FBSV|FBSS|FBCR|FBID|FBLC|FBOP/i.test(Context.getUA());
            };
            Context.isAndroidNative = function () {
                return Context.getBrowser().name === 'Android Browser';
            };
            Context.isAndroid = function () {
                return Context.getOS().name === 'Android' || /Android/i.test(Context.getUA());
            };
            Context.isIos = function () {
                return Context.getOS().name === 'iOS' || Context.isIpad() || Context.isIphone();
            };
            Context.isIphone = function () {
                return Context.getDevice().model === 'iPhone' || /iPhone/i.test(Context.getUA());
            };
            Context.isAndroidMobile = function () {
                return Context.isAndroid() && Context.isMobile();
            };
            Context.isOldIE = function (maxVersion) {
                if (maxVersion === void 0) { maxVersion = 9; }
                return Context.isIE() && Context.getBrowser().major && parseInt(Context.getBrowser().major, 10) <= maxVersion;
            };
            Context.isIE = function () {
                return Context.getBrowser().name === 'IE' || /MSIE|Trident/.test(Context.getUA());
            };
            Context.isChrome = function () {
                return Context.getBrowser().name === 'Chrome' || !!window.chrome;
            };
            Context.isFirefox = function () {
                return Context.getBrowser().name === 'Firefox' || /Firefox/i.test(Context.getUA());
            };
            Context.isAmp = function () {
                return !!window._mainElement_amp;
            };
            Context.isAmpObserveIntersection = function () {
                return Context.isAmp() && !!(window.context && window.context.observeIntersection);
            };
            Context.getIEVersion = function () {
                return Context.isIE() && Context.getBrowser().major ? parseInt(Context.getBrowser().major, 10) : null;
            };
            Context.getAndroidVersion = function () {
                return Context.isAndroid() ? parseInt(Context.getOS().version.split('.').join(), 10) : null;
            };
            Context.getIosVersion = function () {
                return Context.isIos() ? parseInt(Context.getOS().version.split('.').join(), 10) : null;
            };
            Context.isUIWebview = function () {
                return (Context.isIphone() || Context.isIpad())
                    && !/Safari/i.test(Context.getUA())
                    && !window.navigator.standalone;
            };
            Context.videoSupport = function (context) {
                return !!context.createElement('video').canPlayType;
            };
            Context.getLanguage = function () {
                return (window.navigator.language || window.navigator.browserLanguage || window.navigator.userLanguage || 'en');
            };
            Context.getUA = function () {
                return Context.userAgent;
            };
            Context.getDevice = function () {
                if (!this.device) {
                    this.device = new UADevice(mainElement.Ua.mapper.rgx.apply(this, mainElement.Ua.regexes.device));
                }
                return this.device;
            };
            Context.getOS = function () {
                if (!this.os) {
                    this.os = new UAOs(mainElement.Ua.mapper.rgx.apply(this, mainElement.Ua.regexes.os));
                }
                return this.os;
            };
            Context.getBrowser = function () {
                if (!this.browser) {
                    this.browser = new UABrowser(mainElement.Ua.mapper.rgx.apply(this, mainElement.Ua.regexes.browser));
                }
                return this.browser;
            };
            Context.userAgent = navigator.userAgent;
            return Context;
        })();
        mainElement.Context = Context;
    })(mainElement || (mainElement = {}));
}
