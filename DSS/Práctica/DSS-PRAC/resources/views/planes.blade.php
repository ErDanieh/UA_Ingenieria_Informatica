@extends('layouts.principal')

<title>Planes de pago</title>

<style>
  .card {
    border: none;
    padding: 10px 50px;
  }

  .card::after {
    position: absolute;
    z-index: -1;
    opacity: 0;
    -webkit-transition: all 0.6s cubic-bezier(0.165, 0.84, 0.44, 1);
    transition: all 0.6s cubic-bezier(0.165, 0.84, 0.44, 1);
  }

  .card:hover {
    transform: scale(1.02, 1.02);
    -webkit-transform: scale(1.02, 1.02);
    backface-visibility: hidden;
    will-change: transform;
    box-shadow: 0 1rem 3rem rgba(0, 0, 0, .75) !important;
  }

  .card:hover::after {
    opacity: 1;
  }

  .card:hover .btn-outline-primary {
    color: white;
    background: #007bff;
  }
</style>

@section('content')
<div class="container-fluid min-vh-100" style="background: linear-gradient(45deg, #2937f0, #9f1ae2);">
  <div class="container p-5">
    <div class="row">
      <div class="col-lg-6 col-md-12 mb-6">
        <div class="card h-100 shadow-lg">
          <div class="card-body">
            <div class="text-center p-3">
              <h5 class="card-title">BÁSICO</h5>
              <br><br>
              <span class="h2">Gratis</span>
              <br>
            </div>
          </div>
          <ul class="list-group list-group-flush">
            <li class="list-group-item"><svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-check" viewBox="0 0 16 16">
                <path d="M10.97 4.97a.75.75 0 0 1 1.07 1.05l-3.99 4.99a.75.75 0 0 1-1.08.02L4.324 8.384a.75.75 0 1 1 1.06-1.06l2.094 2.093 3.473-4.425a.267.267 0 0 1 .02-.022z" />
              </svg> Acceso limitado a los entrenamientos</li>
          </ul>
          <div class="card-body text-center">
            <a href="/register" class="btn btn-outline-primary btn-lg" style="border-radius:30px">Select</a>
          </div>
        </div>
      </div>
      <div class="col-lg-6 col-md-12 mb-6">
        <div class="card h-100 shadow-lg">
          <div class="card-body">
            <div class="text-center p-3">
              <h5 class="card-title">STANDARD</h5>
              <br><br>
              <span class="h2">14,99€</span>/mes
              <br><br>
            </div>
          </div>
          <ul class="list-group list-group-flush">
            <li class="list-group-item"><svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-check" viewBox="0 0 16 16">
                <path d="M10.97 4.97a.75.75 0 0 1 1.07 1.05l-3.99 4.99a.75.75 0 0 1-1.08.02L4.324 8.384a.75.75 0 1 1 1.06-1.06l2.094 2.093 3.473-4.425a.267.267 0 0 1 .02-.022z" />
              </svg> Acceso ilimitado a los entrenamientos</li>
            <li class="list-group-item"><svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-check" viewBox="0 0 16 16">
                <path d="M10.97 4.97a.75.75 0 0 1 1.07 1.05l-3.99 4.99a.75.75 0 0 1-1.08.02L4.324 8.384a.75.75 0 1 1 1.06-1.06l2.094 2.093 3.473-4.425a.267.267 0 0 1 .02-.022z" />
              </svg>Contacto directo con nuestros entrenadores</li>
          </ul>
          <div class="card-body text-center">
            <div id="paypal-button-container-P-9KM998608Y039742PMKIPDSA"></div>
            <script src="https://www.paypal.com/sdk/js?client-id=Ad0fwF_VBnjzBdnDzW2ZzCx4qAwjxWUFQtWzm96rdFz_v1eXX40J3Sk9VFuNdVuLWhnGhJt6kHQT8LNy&vault=true&intent=subscription" data-sdk-integration-source="button-factory"></script>
            <script>
              paypal.Buttons({
                style: {
                  shape: 'rect',
                  color: 'blue',
                  layout: 'vertical',
                  label: 'subscribe'
                },
                createSubscription: function(data, actions) {
                  return actions.subscription.create({
                    /* Creates the subscription */
                    plan_id: 'P-9KM998608Y039742PMKIPDSA'
                  });
                },
                onApprove: function(data, actions) {
                  alert(data.subscriptionID); // You can add optional success message for the subscriber here
                }
              }).render('#paypal-button-container-P-9KM998608Y039742PMKIPDSA'); // Renders the PayPal button
            </script>
          </div>
        </div>
      </div>
    </div>
    </body>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/js/bootstrap.bundle.min.js" integrity="sha384-ygbV9kiqUc6oa4msXn9868pTtWMgiQaeYH7/t7LECLbyPA2x65Kgf80OJFdroafW" crossorigin="anonymous"></script>
  </div>
  @endsection