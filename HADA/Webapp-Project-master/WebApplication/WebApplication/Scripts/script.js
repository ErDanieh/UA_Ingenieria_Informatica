$(function() {
  var $asientos = $('#yeti');
  var $transitionList = $('#transitionList');

  $('#transitioner').click(function() {
    MotionUI.animateIn($yeti, $transitionList.val());
  });
});
