

// Navigation
$(document).ready(function () {
  $('.ctrl-button').on('mouseup', function () {
    stop()
  })

  $('#forward').on('mousedown', function () {
    forward()
  })

  $('#reverse').on('mousedown', function () {
    reverse()
  })

  $('#left').on('mousedown', function () {
    // turnLeft()
    turnRight()
  })

  $('#right').on('mousedown', function () {
    // turnRight()
    turnLeft()
  })

  // left = 37, up = 38, right = 39, down = 40
  $(document).keydown(function (e) {
    switch (e.which) {
      case 37:
        //turnLeft()
        turnRight()
        break;
      case 38:
        forward()
        break;
      case 39:
        //turnRight()
        turnLeft()
        break;
      case 40:
        reverse()
        break;
      default:
        stop()
    }
    // e.preventDefault();
  })

  $(document).keyup(function (e) {
    stop()
  })

})

function turnLeft() {
  $.get(mobot + "left", function (response) {

  }).fail(function () { alert("left failed") })
}

function turnRight() {
  $.get(mobot + "right", function (response) {

  }).fail(function () { alert("right failed") })
}

function forward() {
  $.get(mobot + "forward", function (response) {

  }).fail(function () { alert("forward failed") })
}

function reverse() {
  $.get(mobot + "reverse", function (response) {

  }).fail(function () { alert("reverse failed") })
}

function stop() {
  $.get(mobot + "stop", function (response) {

  }).fail(function () { alert("stop failed") })
}