import React, { useState, useEffect, useRef, createRef } from 'react';
import { useParams } from 'react-router-dom';
import styled from 'styled-components';
import { DragDropContext } from 'react-beautiful-dnd';
import { useQuery, gql } from '@apollo/client';
import Step from './Step';

const Container = styled.div`
display: flex;
`;

const Candidate: React.FC = (props: any) => {
  const { id } = useParams();
  const { loading, error, data } = useQuery(gql`query getCandidate($candidateId: ID!) {
    candidateById(id: $candidateId) {
      id
      fullname
      email
      phone
      jobs {
        id
        title
      }
      address
      salaryExpectation
      timezone
      steps {
        id
        job {
          id
          title
        }
        step
      }
      resumeFilename
      coverLetter
    }
  }`, {variables: {candidateId: id}});
  const canvases = useRef<Array<HTMLCanvasElement> | null | any>([]);
  const [pdf, setPdf] = useState<any>(null);

  useEffect(() => {
    (async function () {
      if (pdf) {
        for (let i = 0; i < pdf.numPages; i++) {
          const page = await pdf.getPage(i + 1);
          const viewport = page.getViewport({ scale: 1.5 });

          // Prepare canvas using PDF page dimensions.
          const canvas: any = canvases.current[i];
          const canvasContext = canvas.getContext('2d');
          canvas.height = viewport.height;
          canvas.width = viewport.width;

          // Render PDF page into canvas context.
          const renderContext = { canvasContext, viewport };
          page.render(renderContext);
        }
      }
    })();
  }, [pdf]);

  useEffect(() => {

    (async function () {
      const pdfJS = await import('pdfjs-dist/build/pdf');
      pdfJS.GlobalWorkerOptions.workerSrc =
        window.location.origin + '/pdf.worker.min.js';
      const pdf = await pdfJS.getDocument(process.env.REACT_APP_STATIC_URL + '/' + data.candidateById.resumeFilename).promise;
      setPdf(pdf);

    })();
  }, [data]);

  return (<>
    {data && pdf ?
      [...Array(pdf.numPages)].map((_, i) =>
      <canvas ref={(e) => canvases.current[i] = e} style={{ height: '100vh' }} />) :
      <>Loading...</>}
  </>);
};

export default Candidate;
