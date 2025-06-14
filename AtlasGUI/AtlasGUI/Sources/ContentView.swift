//
//  ContentView.swift
//  AtlasGUI
//
//  Created by Sinan Karasu on 6/13/25.
//

// Step 2: In AtlasGUI/ContentView.swift (SwiftUI GUI)
import SwiftUI
internal import Combine


//@MainActor
//class OutputModel: ObservableObject {
//	@Published var output = ""
//}


@MainActor
class LogViewModel: ObservableObject {
	@Published var output = ""
	
	private let reader = PipeReader()
	
	init() {
		reader.startReading { line in
			DispatchQueue.main.async {
				self.output += line + "\n"
			}
		}
	}
}


struct ContentView: View {
	@StateObject private var model = LogViewModel()
	let reader = PipeReader()
	
	var body: some View {
		VStack {
			ScrollView {
				ScrollView {
					Text(model.output).font(.system(.body, design: .monospaced))
						.frame(maxWidth: .infinity, alignment: .leading)
					
				}
				.padding()
			}
			//.onAppear {
			//}
		}
	}
}

#Preview {
	ContentView()
}
