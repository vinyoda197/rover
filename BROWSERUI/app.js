var PhCorrection = 18; //8.57   // change this value to make PH as 7 when not in use.
var TurbCorrection = -1000

var map = null
var mobot =  'http://192.168.1.183/'
var currentDataRow = 0
var $dataRow = null

var $location = null,
  $temperature = null,
  $humidity = null,
  $water = null,
  $turbidity = null,
  $ph = null,
  // $light = null,
  $timestamp = null


$('#loading').css('opacity', 0);

function initMap() {
  var home = { lat: 14.6042004, lng: 120.9822006 }
  var zoom = 5

  map = new google.maps.Map(
    document.getElementById('map'), { zoom: zoom, center: home });
  // The marker, positioned at home
  var marker = new google.maps.Marker({ position: home, map: map });
}

function startDataCollection() {

  currentDataRow = Math.random()

  addTableRow(currentDataRow)

  $('#loading').css('opacity', 1);

  
  getData()
  
  $.get(mobot + "location?t=" + Math.random(), function (response) {
    try {
      $location = JSON.parse(response.trim())
      $dataRow.find('.loc').html($location.Lat + ',' + $location.Lng)
      moveToLocation($location.Lat, $location.Lng)
      saveSendData()
    } catch (e) {
    }
  }).fail(function () { alert("failed getting location") })

  /*
  $.get(mobot + "dht?t=" + Math.random(), function (response) {
    try {
      var dht = JSON.parse(response.trim())
      $temperature = dht.Temperature
      $humidity = dht.Humidity
      $dataRow.find('.temp').html($temperature + 'C')
      $dataRow.find('.humid').html($humidity + '%')
      saveSendData()
    } catch (e) {

    }
  }).fail(function () { alert("failed getting temperature") })

  $.get(mobot + "turbidity?t=" + Math.random(), function (response) {
    try {
      var t = JSON.parse(response.trim())
      var volt = t.Voltage
      var ntu = 0

      volt = volt * 4.2 / 3.2
      volt = Math.round(volt * 10) / 10
      if (volt < 2.5) {
        ntu = 3000
      } else {
        ntu = -1120.4 * volt * volt + 5742.3 * volt - 4353.8
      }

      ntu = ntu - TurbCorrection
      $turbidity = ntu < 0 ? 0 : ntu
      // $turbidity = t.Turbidity

      // resolve water state
      $water = $turbidity > 5 ? 1 : 0
      $dataRow.find('.wat').html($water)

      $dataRow.find('.turb').html(Math.round($turbidity * 100) / 100)
      saveSendData()
    } catch (e) {

    }
  }).fail(function () { alert("failed getting turbidity data") })


  $.get(mobot + "ph?t=" + Math.random(), function (response) {
    try {
      var p = parseFloat(response.trim()) - PhCorrection
      $dataRow.find('.ph').html(p)
      saveSendData()
    } catch (e) {

    }
  }).fail(function () { alert("failed getting ph data") })
  */
}


function saveSendData () {
  if ($location !== null &&
    $temperature !== null &&
    $humidity !== null &&
    $turbidity !== null &&
    // $water !== null &&
    $ph !== null /*&&
    $light !== null*/) {
      $('#loading').css('opacity', 0);
      //addToTable()
  }
}

function addTableRow ($id)
{
  var t = $('table tbody')
  var tm = new Date()

  var markup = "<tr id=\"data-row-" + $id + "\">"
    + "<td>" + tm.toLocaleString() + "</td>"
    + "<td class=\"loc\"></td>"
    + "<td class=\"temp\"></td>"
    + "<td class=\"humid\"></td>"
    + "<td class=\"wat\"></td>"
    + "<td class=\"turb\"></td>"
    + "<td class=\"ph\"></td>"
   /* + "<td class=\"light\"></td>"*/
    + "<td></td></tr>"
  $dataRow = $(markup).appendTo(t)
}

function addToTable () {
  var t = $('table tbody')
  var tm = new Date()

  var correctedTurbidity = - (0.02447 * $turbidity * $turbidity) + (24.84 * $turbidity) - 5368

  var correctedPh = (0.002304 * $ph * $ph) - (2.408 * $ph) + 635.4

  var markup = "<tr><td>" + tm.toLocaleString() + "</td><td>"
    + $location.Lat + "," + $location.Lng + "</td><td>"
    + $temperature + "C</td><td>"
    + $humidity + "%</td><td>"
    + $water + "</td><td>"
    + correctedTurbidity + "</td><td>"
    + correctedPh + "</td><td>"
    /*+ $light + "</td><td>"*/
    + '' + "</td><td></tr>";
  t.append(markup)
  $location = $temperature = $humidity = $water = $turbidity = $ph = null
  $('#loading').css('opacity', 0);

  checkDump()
}

function moveToLocation (lat, lng) {
  var center = new google.maps.LatLng(lat, lng)
  new google.maps.Marker({
    position: center,
    map: map
  })
  // using global variable:
  map.panTo(center)
  map.setZoom(16)
}



function servo() {
  $.get(mobot + "servo", function (response) {
    try {
      if (response == 'ok') {
        alert('Dump successful')
      }
    } catch (e) {

    }
  }).fail(function () { alert("dumping failed ") })
}

function checkDump() {
  if ($water > 0 && $turbidity <= 1500 && ($ph > 4 && $ph < 11)) {
    servo()
  }
}

function getData() {
  $.get(mobot + "data?t=" + Math.random(), function (response) {
    if (response == '') {
      //alert ('hey')
      getData()
    }
    try {
      var $data = JSON.parse(response.trim())
      $temperature = $data.Temperature
      $humidity = $data.Humidity

      // turbidity
      var volt = $data.Voltage
      var ntu = 0
      volt = volt * 4.2 / 3.2
      volt = Math.round(volt * 10) / 10
      if (volt < 2.5) {
        ntu = 3000
      } else {
        ntu = -1120.4 * volt * volt + 5742.3 * volt - 4353.8
      }
      // ntu = ntu
      $turbidity = ntu < 0 ? 0 : ntu + TurbCorrection
      $turbidity = Math.abs($turbidity)

      // resolve water state
      $water = $turbidity > 5 ? 1 : 0

      // ph
      var p = parseFloat($data.Ph) + PhCorrection
      $dataRow.find('.ph').html(Math.abs(Math.round(p * 100) / 100))

      $dataRow.find('.wat').html($water)
      $dataRow.find('.turb').html(Math.round($turbidity * 100) / 100)
      $dataRow.find('.temp').html($temperature + 'C')
      $dataRow.find('.humid').html($humidity + '%')
      saveSendData()
    } catch (e) {
    }
  }).fail(function () { alert("failed getting location") })
}