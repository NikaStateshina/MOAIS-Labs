import SwiftUI

class WindowController: ObservableObject {
    @Published var mainWindow: NSWindow?
    @Published var currentWindow: NSWindow?
}

struct Main_page: View {
    @EnvironmentObject var windowController: WindowController
    
    var body: some View {
        HStack {
            Button("Генерация") {
                openGenerationWindow()
            }
            Button("Эксперимент") {
                openExperimentWindow()
            }
        }
        .padding()
        .onAppear {
            if windowController.mainWindow == nil {
                let window = NSApp.keyWindow
                window?.setContentSize(NSSize(width: 500, height: 500))
                windowController.mainWindow = window
            }
        }
    }

    private func openGenerationWindow() {
        closeCurrentWindow()
        let generation = NSHostingController(rootView: Generation())
        let window = NSWindow(
            contentRect: NSRect(x: 0, y: 0, width: 500, height: 500),
            styleMask: [.titled, .closable, .resizable],
            backing: .buffered, defer: false)
        window.contentViewController = generation
        window.title = "Generation Window"
        window.isReleasedWhenClosed = false
        window.center()
        window.makeKeyAndOrderFront(nil)
        windowController.currentWindow = window
        windowController.mainWindow?.orderOut(nil)
    }

    private func openExperimentWindow() {
        closeCurrentWindow()
        let experiment = NSHostingController(rootView: Experiment())
        let window = NSWindow(
            contentRect: NSRect(x: 0, y: 0, width: 500, height: 500),
            styleMask: [.titled, .closable, .resizable],
            backing: .buffered, defer: false)
        window.contentViewController = experiment
        window.title = "Experiment Window"
        window.isReleasedWhenClosed = false
        window.center()
        window.makeKeyAndOrderFront(nil)
        windowController.currentWindow = window
        windowController.mainWindow?.orderOut(nil)
    }

    private func closeCurrentWindow() {
        windowController.currentWindow?.close()
    }
}

struct GenerationView: View {
    @EnvironmentObject var windowController: WindowController
    
    var body: some View {
        VStack {
            Text("This is the Generation window!")
                .font(.largeTitle)
                .padding()
            Button("Назад") {
                openMainWindow()
            }
            .padding()
        }
        .frame(width: 500, height: 500)
    }
    
    private func openMainWindow() {
        windowController.currentWindow?.close()
        windowController.mainWindow?.makeKeyAndOrderFront(nil)
        windowController.currentWindow = nil
    }
}

struct ExperimentView: View {
    @EnvironmentObject var windowController: WindowController
    
    var body: some View {
        VStack {
            Text("This is the Experiment window!")
                .font(.largeTitle)
                .padding()
            Button("Назад") {
                openMainWindow()
            }
            .padding()
        }
        .frame(width: 500, height: 500)
    }
    
    private func openMainWindow() {
        windowController.currentWindow?.close()
        windowController.mainWindow?.makeKeyAndOrderFront(nil)
        windowController.currentWindow = nil
    }
}

@main
struct KursovayaAppView: App {
    @StateObject private var windowController = WindowController()
    
    var body: some Scene {
        WindowGroup {
            Main_page()
                .environmentObject(windowController)
        }
    }
}
