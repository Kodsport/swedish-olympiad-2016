import java.io.IOException;

public class InputValidator {

	public static void main(String... args) throws IOException {
		Context.readInitialConfig(System.in);
		System.exit(42);
	}

}
