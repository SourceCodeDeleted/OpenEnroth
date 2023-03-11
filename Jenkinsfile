pipeline {
  agent any
  stages {
    stage('Getting dependencies') {
      steps {
        // Clean before build
        cleanWs()
        // We need to explicitly checkout from SCM here
        checkout scm
        echo "Building ${env.JOB_NAME}..."
        sh 'mkdir ${WORKSPACE}/build_dependencies'

        sh 'chmod +x buildscripts/dep_builder.sh'
        sh './buildscripts/dep_builder.sh'
      }
    }

   stage('Compiling Project') {
            steps {
                sh 'cd ${WORKSPACE}'
                sh 'cmake -B build -S .'
                sh 'cmake --build build' 
            }
        }


   stage('Updating Release') {
            steps {
                sh 'cd ${WORKSPACE}'
                sh 'zip  build/OpenEnroth_linux.zip build/OpenEnroth'
                sh "gh release create v1.0.0 --title "Open Enroth Linux" --notes "Release made for Linux""
                sh 'gh release upload v1.0.0  build/OpenEnroth_linux.zip --c "OpenEnroth For Linux"'
            }
        }


//    stage('Clean Workspace') {
//             steps {
//                 sh 'cd ${WORKSPACE}'
//                 cleanWs()
//             }
//         }

  }
}