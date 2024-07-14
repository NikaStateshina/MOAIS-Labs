import SwiftUI
import Charts

struct ExperimentResultItem: Identifiable {
    let id = UUID()
    let description: String
    let fileName: String
    let sortType: String
    let timeElapsed: Double
    let comparisons: Int
    let swaps: Int
}

struct Experiment: View {
    @State private var selectedSorts: [String] = []
    @State private var selectedFiles: [URL] = []
    @State private var showAlert = false
    @State private var alertMessage = ""
    @State private var showingResultWindow = false
    @State private var experimentResults: [ExperimentResultItem] = []

    private let sortOptions = ["MSD", "Быстрая"]

    var body: some View {
        VStack {
            VStack(alignment: .leading) {
                Text("Выберите сортировки:")
                    .font(.headline)
                
                ForEach(sortOptions, id: \.self) { sort in
                    Toggle(sort, isOn: Binding(
                        get: { self.selectedSorts.contains(sort) },
                        set: { isSelected in
                            if isSelected {
                                self.selectedSorts.append(sort)
                            } else {
                                self.selectedSorts.removeAll { $0 == sort }
                            }
                        }
                    ))
                }
            }
            .padding()

            VStack(alignment: .leading) {
                Button("Выбрать файлы") {
                    openFilePanel()
                }

                if !selectedFiles.isEmpty {
                    Text("Выбранные файлы:")
                    ForEach(selectedFiles, id: \.self) { file in
                        Text(file.lastPathComponent)
                    }
                }
            }
            .padding()

            HStack {
                Button("Назад") {
                    NSApp.keyWindow?.close()
                }
                .padding()
                
                Button("Запуск эксперимента") {
                    startExperiment()
                }
                .padding()
            }
        }
        .frame(width: 500, height: 500)
        .alert(isPresented: $showAlert) {
            Alert(
                title: Text("Сообщение"),
                message: Text(alertMessage),
                dismissButton: .default(Text("OK"))
            )
        }
        .sheet(isPresented: $showingResultWindow) {
            ExperimentResultView(results: $experimentResults, showingResultWindow: $showingResultWindow)
        }
    }

    private func startExperiment() {
            guard !selectedSorts.isEmpty else {
                alertMessage = "Не выбрана ни одна сортировка"
                showAlert = true
                return
            }

            guard !selectedFiles.isEmpty else {
                alertMessage = "Не выбраны файлы для эксперимента"
                showAlert = true
                return
            }

            experimentResults = []

            for file in selectedFiles {
                do {
                    let content = try String(contentsOf: file, encoding: .utf8)
                    var elements = content.split(separator: " ").map { String($0) }
                    var intElements = elements.compactMap { Int($0) }

                    for sort in selectedSorts {
                        let startTime = CFAbsoluteTimeGetCurrent()
                        var comparisons = 0
                        var swaps = 0
                        if sort == "MSD" {
                            SortingAlgorithms.radixSort(&elements)

                        } else if sort == "Быстрая" {
                            SortingAlgorithms.quickSortHoare(&intElements, comparisons: &comparisons, swaps: &swaps)
                            // Преобразуем intElements обратно в elements
                            elements = intElements.map { String($0) }
                        }
                        let timeElapsed = CFAbsoluteTimeGetCurrent() - startTime
                        
                        //Вывод времени выполнения в консоль
                        //print("Файл: \(file.lastPathComponent), Сортировка: \(sort), Время: \(timeElapsed)")
                        
                        // Записываем отсортированный массив в файл
                        try saveSortedArrayToFile(elements, fileName: file.lastPathComponent, sortType: sort)


                        experimentResults.append(ExperimentResultItem(
                            description: "\(file.lastPathComponent): Сортировка \(sort) заняла \(timeElapsed) секунд, сравнений: \(comparisons), пересылок: \(swaps)",
                            fileName: file.lastPathComponent,
                            sortType: sort,
                            timeElapsed: timeElapsed,
                            comparisons: comparisons,
                            swaps: swaps
                        ))
                        //print("Добавлено в experimentResults: \(experimentResults.last!)")
                    }
                } catch {
                    alertMessage = "Ошибка при чтении файла \(file.lastPathComponent): \(error.localizedDescription)"
                    showAlert = true
                    return
                }
            }

        //print("Experiment results: \($experimentResults.timeElapsed)") // Отладочная информация

            showingResultWindow = true
        }
    
    private func saveSortedArrayToFile(_ array: [String], fileName: String, sortType: String) throws {
        let fileManager = FileManager.default

        // Получаем путь к рабочему столу
        if let desktopDirectory = fileManager.urls(for: .desktopDirectory, in: .userDomainMask).first {
            // Создаем директорию output на рабочем столе
            let directoryURL = desktopDirectory.appendingPathComponent("output")
            if !fileManager.fileExists(atPath: directoryURL.path) {
                try fileManager.createDirectory(at: directoryURL, withIntermediateDirectories: true, attributes: nil)
            }

            // Создаем имя файла для отсортированных данных
            let sortedFileName = fileName.replacingOccurrences(of: ".txt", with: "_sorted_\(sortType).txt")
            let fileURL = directoryURL.appendingPathComponent(sortedFileName)

            // Записываем отсортированный массив в файл
            try array.joined(separator: " ").write(to: fileURL, atomically: true, encoding: .utf8)
        } else {
            throw NSError(domain: "Sorting", code: 1, userInfo: [NSLocalizedDescriptionKey: "Не удалось найти рабочий стол"])
        }
    }
    

    private func openFilePanel() {
        let panel = NSOpenPanel()
        panel.allowsMultipleSelection = true
        panel.canChooseFiles = true
        panel.canChooseDirectories = false
        //panel.allowedFileTypes = ["txt"]

        // Получаем путь к рабочему столу
        if let desktopDirectory = FileManager.default.urls(for: .desktopDirectory, in: .userDomainMask).first {
            // Указываем подкаталог внутри Desktop
            let directoryURL = desktopDirectory.appendingPathComponent("input")
            
            if FileManager.default.fileExists(atPath: directoryURL.path) {
                panel.directoryURL = directoryURL
            } else {
                print("Directory does not exist: \(directoryURL.path)")
            }
        } else {
            print("Desktop directory not found")
        }
        
        panel.begin { response in
            if response == .OK {
                // Проверка выбранных файлов на наличие расширения .txt
                self.selectedFiles = panel.urls.filter { $0.pathExtension == "txt" }
                if self.selectedFiles.isEmpty {
                    self.alertMessage = "Выберите файлы с расширением .txt"
                    self.showAlert = true
                }
                print("Selected files: \(self.selectedFiles)")
            } else {
                print("User cancelled file selection")
            }
        }
    }
}

struct ExperimentResultView: View {
    @Binding var results: [ExperimentResultItem]
    @Binding var showingResultWindow: Bool

    var body: some View {
        VStack {
            Text("Результаты эксперимента")
                .font(.largeTitle)
                .padding()
            
            if results.isEmpty {
                Text("Нет данных для отображения")
                    .padding()
            } else {
                List(results) { result in
                    Text(result.description)
                }
                ChartView(results: results)
            }

            Button("Закрыть") {
                showingResultWindow = false
            }
            .padding()
        }
        .frame(width: 700, height: 600)
        .onAppear {
        }
    }
}

struct ChartView: View {
    var results: [ExperimentResultItem]

    var body: some View {
        HStack {
            VStack {
                Text("Время выполнения (мс)")
                    .font(.headline)
                Chart {
                    ForEach(results) { result in
                        BarMark(
                            x: .value("Файл", result.fileName),
                            y: .value("Время", result.timeElapsed * 1000)
                        )
                        .foregroundStyle(by: .value("Тип сортировки", result.sortType))
                        .position(by: .value("Тип сортировки", result.sortType))
                    }
                }
                .frame(height: 300)
            }
//            VStack {
//                Text("Количество пересылок")
//                    .font(.headline)
//                Chart {
//                    ForEach(results) { result in
//                        BarMark(
//                            x: .value("Файл", result.fileName),
//                            y: .value("Пересылки", result.swaps)
//                        )
//                        .foregroundStyle(by: .value("Тип сортировки", result.sortType))
//                    }
//                }
//                .frame(height: 300)
//            }
        }
        .padding()
        .onAppear {
            for result in results {
                print("Файл: \(result.fileName), Сортировка: \(result.sortType), Время: \(result.timeElapsed * 1000)")
            }
        }
    }
}

struct Experiment_Previews: PreviewProvider {
    static var previews: some View {
        Experiment()
    }
}
