package gen;

import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;

public class Submission {

	private static final String[] cases = {
		"robot_concentric",
		"robot_cross",
		"robot_diagonal",
		"robot_ew_manuell",
		"robot_path_freedom",
		"robot_path_freedom2",
		"robot_rand_60",
		"robot_rand_80",
		"robot_maze",
		"robot_spiral"
	};

	public static void main(String... args) throws Exception {
		String submission = "";

		submission += "ans = {\n";

		for (String name : cases){
			String text = new String(Files.readAllBytes(Paths.get(name + ".ans")), StandardCharsets.UTF_8);
			submission += "'" + name + "': \"\"\"" + text + "\"\"\",";
		}

		submission += "}\n";
		submission += "casename = input()\n";
		submission += "print (ans[casename])\n";
		
		FileWriter fw = new FileWriter("robot.py");
		fw.write(submission);
		fw.close();
	}

}
