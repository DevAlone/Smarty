import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }

        // Additional import path used to resolve QML modules in Qt Creator's code model
        property pathList qmlImportPaths: []

        cpp.cxxLanguageVersion: "c++14"

        cpp.defines: [
            // The following define makes your compiler emit warnings if you use
            // any feature of Qt which as been marked deprecated (the exact warnings
            // depend on your compiler). Please consult the documentation of the
            // deprecated API in order to know how to port your code away from it.
            "QT_DEPRECATED_WARNINGS",

            // You can also make your code fail to compile if you use deprecated APIs.
            // In order to do so, uncomment the following line.
            // You can also select to disable deprecated APIs only up to a certain version of Qt.
            //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
        ]

        cpp.systemIncludePaths: [
            "."
        ]

        files: [
            "BackgroundInputProcessor.cpp",
            "BackgroundInputProcessor.h",
            "qfreedesktop/Icon.cpp",
            "qfreedesktop/Icon.h",
            "qfreedesktop/IconDatabase.cpp",
            "qfreedesktop/IconDatabase.h",
            "IconProcessor.cpp",
            "IconProcessor.h",
            "ImageProvider.cpp",
            "ImageProvider.h",
            "InputParser.cpp",
            "InputParser.h",
            "InputProcessor.cpp",
            "InputProcessor.h",
            "Item.cpp",
            "Item.h",
            "ModulesManager.cpp",
            "ModulesManager.h",
            "ModulesManagerBackgroundWorker.cpp",
            "ModulesManagerBackgroundWorker.h",
            "RunGuard.cpp",
            "RunGuard.h",
            "SmartyApplication.cpp",
            "SmartyApplication.h",
            "TextItem.cpp",
            "TextItem.h",
            "qfreedesktop/README.md",
            "smart_modules/Module.cpp",
            "smart_modules/Module.h",
            "main.cpp",
            "qml.qrc",
            "smart_modules/run_program_module/ProgramItem.cpp",
            "smart_modules/run_program_module/ProgramItem.h",
            "smart_modules/run_program_module/RunProgramModule.cpp",
            "smart_modules/run_program_module/RunProgramModule.h",
            "smart_modules/modules.h",
            "qfreedesktop/DesktopEntryFile.cpp",
            "qfreedesktop/DesktopEntryFile.h",
            "qfreedesktop/IconFile.cpp",
            "qfreedesktop/IconFile.h",
            "smart_modules/run_program_module/RunProgramModuleProgram.cpp",
            "smart_modules/run_program_module/RunProgramModuleProgram.h",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: product.type
            qbs.install: true
        }
    }
}
