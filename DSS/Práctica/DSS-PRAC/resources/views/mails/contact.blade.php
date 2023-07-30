<!doctype html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0">
    <title>Llamado de emergencia</title>
</head>

<body>
    <div style="margin-top: 50px; display: flex; flex-direction: row; justify-content: space-between;">
        <img src={{Auth::user()->picture}} style="height: 300px; width: 250px; object-fit:cover; border-radius: 10px;" />

        <div style="display: flex; flex-direction: column; margin-right: min(100px); justify-content: center;">
            <label>Email:</label>
            <h3>{{Auth::user()->email}}</h3>
            <h2>{{$mensaje}}</h2>
        </div>
    </div>

</body>

</html>