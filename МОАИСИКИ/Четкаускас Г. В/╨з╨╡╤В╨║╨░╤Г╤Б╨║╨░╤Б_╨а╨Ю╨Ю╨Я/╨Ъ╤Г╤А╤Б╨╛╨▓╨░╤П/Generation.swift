import SwiftUI
import Combine

struct Generation: View {
    @State private var numberOfElements: String = ""
    @State private var minDigits: String = ""
    @State private var maxDigits: String = ""
    @State private var sequenceType: SequenceType = .nonDecreasing
    @State private var showAlert = false
    @State private var alertMessage = ""

    var body: some View {
        VStack {
            HStack {
                VStack(alignment: .leading) {
                    Text("Введите количество элементов")
                    TextField("", text: $numberOfElements)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .onReceive(Just(numberOfElements)) { newValue in
                            let filtered = newValue.filter { "0123456789".contains($0) }
                            if filtered != newValue {
                                self.numberOfElements = filtered
                            }
                        }

                    Text("Введите минимальное количество разрядов")
                    TextField("", text: $minDigits)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .onReceive(Just(minDigits)) { newValue in
                            let filtered = newValue.filter { "0123456789".contains($0) }
                            if filtered != newValue {
                                self.minDigits = filtered
                            }
                        }

                    Text("Введите максимальное количество разрядов")
                    TextField("", text: $maxDigits)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .onReceive(Just(maxDigits)) { newValue in
                            let filtered = newValue.filter { "0123456789".contains($0) }
                            if filtered != newValue {
                                self.maxDigits = filtered
                            }
                        }
                }
                .padding()

                VStack(alignment: .leading) {
                    Group {
                        Text("Тип последовательности")
                        Picker("", selection: $sequenceType) {
                            ForEach(SequenceType.allCases) { type in
                                Text(type.rawValue).tag(type)
                            }
                        }
                        .pickerStyle(RadioGroupPickerStyle())
                        .frame(maxWidth: .infinity, alignment: .leading)
                    }
                }
                .padding()
            }

            HStack {
                Button("Назад") {
                    NSApp.keyWindow?.close()
                }
                .padding()

                Button("Сгенерировать последовательность") {
                    generateFiles()
                }
                .padding()
            }
        }
        .alert(isPresented: $showAlert) {
            Alert(title: Text("Сообщение!"), message: Text(alertMessage), dismissButton: .default(Text("OK")))
        }
        .frame(width: 700, height: 500)
    }

    private func generateFiles() {
        guard !numberOfElements.isEmpty, !minDigits.isEmpty, !maxDigits.isEmpty else {
            alertMessage = "Не все поля заполнены"
            showAlert = true
            return
        }

        guard let numberOfElements = Int(numberOfElements), numberOfElements >= 2, numberOfElements <= 1000000 else {
            alertMessage = "Некорректное количество элементов"
            showAlert = true
            return
        }

        guard let minDigits = Int(minDigits), minDigits >= 2, minDigits <= 10 else {
            alertMessage = "Некорректное минимальное количество разрядов"
            showAlert = true
            return
        }

        guard let maxDigits = Int(maxDigits), maxDigits >= 2, maxDigits <= 10, maxDigits >= minDigits else {
            alertMessage = "Некорректное максимальное количество разрядов"
            showAlert = true
            return
        }

        do {
            let fileName = try FileGenerator.generateFile(numberOfElements: numberOfElements, minDigits: minDigits, maxDigits: maxDigits, sequenceType: sequenceType)
            alertMessage = "Файл успешно сгенерирован: \(fileName)"
        } catch {
            alertMessage = "Ошибка при генерации файла: \(error.localizedDescription)"
        }

        showAlert = true
    }

}

struct Generation_Previews: PreviewProvider {
    static var previews: some View {
        Generation()
    }
}
