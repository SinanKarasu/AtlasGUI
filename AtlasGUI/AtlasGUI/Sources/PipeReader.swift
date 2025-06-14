//
//  PipeReader.swift
//  AtlasGUI
//
//  Created by Sinan Karasu on 6/13/25.
//

// Step 3: PipeReader.swift (create in AtlasGUI)
import Foundation

class PipeReader {
	private var process: Process?
	private var pipe: Pipe?
	
	func startReading(onLine: @escaping (String) -> Void) {
		let process = Process()
		let pipe = Pipe()
		self.process = process
		self.pipe = pipe
		
//		let fileManager = false;
//		if fileManager {
//			let home = FileManager.default.homeDirectoryForCurrentUser
//			let path = home.appendingPathComponent("bin/AtlasCL").path
//			process.executableURL = URL(fileURLWithPath: path)
//		} else {
//			//process.executableURL = URL(fileURLWithPath: "${HOME}/bin/AtlasCL")
//			process.executableURL = URL(fileURLWithPath: "/Users/sinan/bin/AtlasCL")
//		}
		
		let home = FileManager.default.homeDirectoryForCurrentUser
		let path = home.appendingPathComponent("bin/AtlasCL").path
		process.executableURL = URL(fileURLWithPath: path)

		process.standardOutput = pipe
		process.standardError = pipe
		
		let handle = pipe.fileHandleForReading
		handle.readabilityHandler = { fileHandle in
			if let line = String(data: fileHandle.availableData, encoding: .utf8), !line.isEmpty {
				onLine(line.trimmingCharacters(in: .whitespacesAndNewlines))
			}
		}
		
		do {
			try process.run()
		} catch {
			print("Failed to run AtlasCL: \(error)")
		}
	}
}
