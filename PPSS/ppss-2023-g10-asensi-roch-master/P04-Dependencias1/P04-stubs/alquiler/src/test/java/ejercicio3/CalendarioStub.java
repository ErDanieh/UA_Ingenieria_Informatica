package ejercicio3;
import java.time.LocalDate;
import java.util.List;

public class CalendarioStub extends Calendario{
    List<Integer> diafest;
    List<Integer> exception;

    public CalendarioStub(List<Integer> diafest, List<Integer> exception) {
        this.diafest = diafest;
        this.exception = exception;
    }

    @Override
    public boolean es_festivo(LocalDate dia) throws CalendarioException {
        if (diafest.contains(dia.getDayOfMonth())) {
            return true;
        } else if (exception.contains(dia.getDayOfMonth())) {
            throw new CalendarioException("Error en dia: " + dia + ";");
        } else
            return false;
    }
}
