import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import 'antd/dist/antd.min.css';
import 'react-toastify/dist/ReactToastify.css';
import { ApolloClient, InMemoryCache, ApolloProvider, gql } from '@apollo/client';
import Login from './Login'
import {
  BrowserRouter as Router,
  Routes,
  Route,
} from "react-router-dom";
import { ToastContainer } from 'react-toastify';
import reportWebVitals from './reportWebVitals';
import JobBoard from './JobBoard';
import JobsTable from './JobsTable';
import Layout from './Layout';
import CandidatesTable from './CandidatesTable';
import Candidate from './Candidate';
import Dashboard from './Dashboard';

const client = new ApolloClient({
  uri: process.env.REACT_APP_API_URL + '/graphql',
  cache: new InMemoryCache(),
});

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <ApolloProvider client={client}>
      <Router>
        <Layout>
          <Routes>
            <Route path="/" element={<Login />} />
            <Route path="/job/:id" element={<JobBoard />} />
            <Route path="/jobs" element={<JobsTable />} />
            <Route path="/candidate/:id" element={<Candidate />} />
            <Route path="/candidates" element={<CandidatesTable />} />
            <Route path="/dashboard" element={<Dashboard />} />
          </Routes>
        </Layout>
      </Router>
      <ToastContainer />
    </ApolloProvider>
  </React.StrictMode>
);

reportWebVitals();
