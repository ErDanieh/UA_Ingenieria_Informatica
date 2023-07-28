package ejercicio4;

public class ReservaTestable extends Reserva{
    private String validLogin;
    private String validPassword;

    private Usuario validUser;


    public void setValidLogin(String validLogin){
        this.validLogin = validLogin;
    }

    public void setValidPassword(String validPassword){
        this.validPassword = validPassword;
    }

    public void setValidUser(Usuario validUser){
        this.validUser =  validUser;
    }

    @Override
    public boolean compruebaPermisos(String login, String password, Usuario tipoUsu) {
        if((login == validLogin) && ( password == validPassword) && (tipoUsu == validUser))
            return true;
        else {
            return false;
        }
    }
}
