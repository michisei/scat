package SlowCat;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

public class Options {
	public static final String USAGE_STATEMENT = 
"""
usage: java SlowCat [options] [file]...
A more simplified and slower tool that mimics the behaviour of the 'cat' command.
The tool will print characters one by one with a specified delay.
It does not retain the full functionalities of the original tool.

Options:
  -h, --help  display this help and exit.
  -d, --delay specify delay for each character in milliseconds.
              Note: Java Edition does not accept decimals.

scat Java edition, Build 202502231855.
""";

	public final int delayMs;
	public final List<String> posArgs;
	public final boolean showHelp;
	
	public Options(int delayMS, Stream<String> posArgs, boolean showHelp) {
		this.delayMs = delayMS;
		this.posArgs = posArgs.toList();
		this.showHelp = showHelp;
	}

	private static void cpyPosArgs(Stream.Builder<String> argBuilder, Stream<String> args) {
		args.forEach(argBuilder::accept);
	}

	private static void printUsage() {
		System.err.format(USAGE_STATEMENT);
	}

	public static Options parseArgs(String[] args) {
		Stream.Builder<String> argBuilder = Stream.builder();
		int delayMs = SlowCat.DEFAULT_DELAY_MS;

		for (int i = 0; i < args.length; i++) {
            switch (args[i]) {
                case "--" -> {
                    cpyPosArgs(argBuilder, Arrays.stream(args, i, args.length));
                    return new Options(delayMs, argBuilder.build(), false);
                }
                case "-h", "--help" -> {
                    printUsage();
                    return new Options(delayMs, argBuilder.build(), true);
                }
                case "-d", "--delay" -> {
                    if (args.length < i + 1) {
                        System.err.println(
                                "[\033[1;31mERROR\033[0m] Missing argument for " + args[i] + "."
                        );
                        System.exit(1);
                    }

                    if (!args[i + 1].chars().allMatch(x -> x >= 48 && x < 58)) {
                        System.err.println(
                                "[\033[1;31mERROR\033[0m] Expecting a number for " + args[i] + "."
                        );
                        System.exit(1);
                    }

                    delayMs = Integer.parseInt(args[i + 1]);
                    i++;
                    continue;
                }
            }

            argBuilder.accept(args[i]);
		}
		return new Options(delayMs, argBuilder.build(), false);
	}
}
