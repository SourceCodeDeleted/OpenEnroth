pipeline {
  agent any
  stages {
    stage('getting dependencies') {
      steps {
        // Clean before build
        cleanWs()
        // We need to explicitly checkout from SCM here
        checkout scm
        echo "Building ${env.JOB_NAME}..."

        sh 'chmod +x buildscripts/dep_builder.sh'
        sh './buildscripts/dep_builder.sh'
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
