package SlowCat;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Optional;

public class SlowCat {
	static final int         DEFAULT_DELAY_MS = 10;
	private static final int READ_BUFFER_SIZE = 1048576;

	public static void main(String[] args) {
		Options opts = Options.parseArgs(args);

		if (opts.showHelp) {
			System.exit(0);
		}

		if (opts.posArgs.isEmpty()) {
			new SlowCat(Optional.empty(), opts.delayMs)
				.write();
			System.exit(0);
		}

		opts.posArgs.stream().map(x -> new SlowCat(Optional.of(x), opts.delayMs))
			.forEach(x -> {
				x.write();
			});
	}

	private final Optional<String> filename;
	private final int sleepMs;

	public SlowCat(Optional<String> fn, int sleepMs) {
		this.filename = fn;
		this.sleepMs = sleepMs;
	}

	public void write() {
		Reader rd = this.filename
			.flatMap(x -> {
				try {
					return Optional.of(x.equals("-") ?
						new InputStreamReader(System.in) : new FileReader(x));
				} catch (FileNotFoundException e) {
					System.err.println(
						"[\033[1;33mWARNING\033[0m] Could not open file '"
						+ this.filename.orElse("- (stdin)") + "'."
					);
					System.err.println(
						"[\033[1;33mWARNING\033[0m] " + e.getMessage()
					);
				}
				System.exit(1);
				return Optional.empty();
			})
			.orElse(new InputStreamReader(System.in));
		try {
			BufferedReader reader = new BufferedReader(rd);
			char[] fragment = new char[READ_BUFFER_SIZE];
			int read_size;
			do {
				read_size = reader.read(fragment);
				String.valueOf(fragment).chars().limit(read_size).forEach(
					c -> {
						System.out.print(String.valueOf((char) c));
						System.out.flush();
						try {
							Thread.sleep(this.sleepMs);
						} catch (InterruptedException e) {}
					}
				);
			} while (read_size == READ_BUFFER_SIZE);

			reader.close();
		} catch (IOException e) {
			System.err.println(
				"[\033[1;33mWARNING\033[0m] Could not read file '" + this.filename + "'."
			);
			System.err.println(
				"[\033[1;33mWARNING\033[0m] " + e.getMessage()
			);
		}
	}

}
