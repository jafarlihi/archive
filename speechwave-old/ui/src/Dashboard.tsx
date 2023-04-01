import { Tag, Button, Table, Checkbox, Modal, InputNumber, Dropdown, Menu, Select, Card } from 'antd';
import { DollarOutlined, CheckCircleTwoTone, LogoutOutlined, InboxOutlined, DownloadOutlined, PlusOutlined, CaretDownOutlined, DeleteOutlined, MinusOutlined, EditOutlined, WarningTwoTone } from '@ant-design/icons';
import type { UploadProps } from 'antd';
import { message, Upload } from 'antd';
import type { ColumnsType } from 'antd/es/table';
import { useEffect, useState, useRef } from 'react';
import { useNavigate, useSearchParams } from 'react-router-dom';
import { Elements } from '@stripe/react-stripe-js';
import { loadStripe } from '@stripe/stripe-js';
import { CSVLink } from 'react-csv';
import CheckoutForm from './CheckoutForm';
import logo from './assets/logo.svg';

const { Dragger } = Upload;

function useInterval(callback: any, delay: any) {
  callback();
  const intervalRef = useRef<number>();
  const callbackRef = useRef(callback);
  useEffect(() => {
    callbackRef.current = callback;
  }, [callback]);
  useEffect(() => {
    if (typeof delay === 'number') {
      intervalRef.current = window.setInterval(() => callbackRef.current(), delay);
      return () => window.clearInterval(intervalRef.current);
    }
  }, [delay]);
  return intervalRef;
}

function setIntervalX(callback: any, delay: number, repetitions: number) {
  var x = 0;
  var intervalID = window.setInterval(function () {
    callback();
    if (++x === repetitions) {
      window.clearInterval(intervalID);
    }
  }, delay);
}

function Dashboard(props: any) {
  const [uploads, setUploads] = useState<
  { status: string, uploaded_at: string, original_name: string, filename: string, txt: string, srt: string, vtt: string }[]
  >([]);
  const [refetch, setRefetch] = useState(new Date());
  const [credits, setCredits] = useState(0);
  const [translate, setTranslate] = useState(false);
  const [paymentModalOpen, setPaymentModalOpen] = useState(false);
  const [buyCreditAmount, setBuyCreditAmount] = useState(1000);
  const [apiKeysModalOpen, setApiKeysModalOpen] = useState(false);
  const [creditHistoryModalOpen, setCreditHistoryModalOpen] = useState(false);
  const [apiKeys, setApiKeys] = useState([]);
  const [creditHistory, setCreditHistory] = useState([]);
  const [language, setLanguage] = useState('Auto-detect');
  const [stripePromise, setStripePromise] = useState<any>(null);
  const [clientSecret, setClientSecret] = useState('');
  const [searchParams, setSearchParams] = useSearchParams();
  const [paymentSuccessModalOpen, setPaymentSuccessModalOpen] = useState(false);
  const navigate = useNavigate();

  const languages = ['Afrikaans', 'Albanian', 'Amharic', 'Arabic', 'Armenian', 'Assamese', 'Azerbaijani', 'Bashkir', 'Basque', 'Belarusian', 'Bengali', 'Bosnian', 'Breton', 'Bulgarian', 'Burmese', 'Castilian', 'Catalan', 'Chinese', 'Croatian', 'Czech', 'Danish', 'Dutch', 'English', 'Estonian', 'Faroese', 'Finnish', 'Flemish', 'French', 'Galician', 'Georgian', 'German', 'Greek', 'Gujarati', 'Haitian', 'Haitian Creole', 'Hausa', 'Hawaiian', 'Hebrew', 'Hindi', 'Hungarian', 'Icelandic', 'Indonesian', 'Italian', 'Japanese', 'Javanese', 'Kannada', 'Kazakh', 'Khmer', 'Korean', 'Lao', 'Latin', 'Latvian', 'Letzeburgesch', 'Lingala', 'Lithuanian', 'Luxembourgish', 'Macedonian', 'Malagasy', 'Malay', 'Malayalam', 'Maltese', 'Maori', 'Marathi', 'Moldavian', 'Moldovan', 'Mongolian', 'Myanmar', 'Nepali', 'Norwegian', 'Nynorsk', 'Occitan', 'Panjabi', 'Pashto', 'Persian', 'Polish', 'Portuguese', 'Punjabi', 'Pushto', 'Romanian', 'Russian', 'Sanskrit', 'Serbian', 'Shona', 'Sindhi', 'Sinhala', 'Sinhalese', 'Slovak', 'Slovenian', 'Somali', 'Spanish', 'Sundanese', 'Swahili', 'Swedish', 'Tagalog', 'Tajik', 'Tamil', 'Tatar', 'Telugu', 'Thai', 'Tibetan', 'Turkish', 'Turkmen', 'Ukrainian', 'Urdu', 'Uzbek', 'Valencian', 'Vietnamese', 'Welsh', 'Yiddish', 'Yoruba'];

  useEffect(() => {
    if (searchParams.get('paymentSuccess') === 'true') {
      if (localStorage.getItem('last_payment_intent') !== searchParams.get('payment_intent'))
        setPaymentSuccessModalOpen(true);
      localStorage.setItem('last_payment_intent', searchParams.get('payment_intent') ?? '');
      setIntervalX(() => {
        setRefetch(new Date());
      }, 2500, 10);
    }
  }, [searchParams]);

  const cancelPaymentSuccessModal = () => {
    setPaymentSuccessModalOpen(false);
  };

  const buyCreditAmountChange = (value: number | null) => {
    setBuyCreditAmount(value ?? 0);
  };

  const languageChanged = (value: string) => {
    setLanguage(value);
  };

  const onBuyClick = async () => {
    let resp = await (await fetch(process.env.REACT_APP_API_URL + '/v1/stripe', {
      method: 'GET',
      headers: { Authorization: 'Bearer ' + localStorage.getItem('access') },
    })).json();
    setStripePromise(loadStripe(resp['key']));
    resp = await (await fetch(process.env.REACT_APP_API_URL + '/v1/stripe', {
      method: 'POST',
      headers: { Authorization: 'Bearer ' + localStorage.getItem('access'), 'Content-Type': 'application/json' },
      body: JSON.stringify({ amount: Number(buyCreditAmount * 0.1 * 100) }),
    })).json();
    setClientSecret(resp['key']);
  };

  const onEditClick = async () => {
    setClientSecret('');
  };

  const fetchApiKeys = async () => {
    const response = await (await fetch(
      process.env.REACT_APP_API_URL + '/v1/key',
      { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } },
    )).json();
    setApiKeys(response.keys.map((k: any) => {
      k.created_at = k.created_at.$date;
      return k;
    }));
  };

  const openCreditHistoryModal = async () => {
    const response = await (await fetch(
      process.env.REACT_APP_API_URL + '/v1/credits?detailed=true',
      { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } },
    )).json();
    setCreditHistory(response.history.map((h: any) => {
      h.date = h.date.$date;
      return h;
    }));
    setCreditHistoryModalOpen(true);
  };

  const cancelCreditHistoryModal = async () => {
    setCreditHistoryModalOpen(false);
  };

  const openApiKeysModal = async () => {
    await fetchApiKeys();
    setApiKeysModalOpen(true);
  };

  const generateApiKey = async () => {
    await fetch(
      process.env.REACT_APP_API_URL + '/v1/key',
      { method: 'POST', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') }}
    );
    await fetchApiKeys();
  };

  const cancelApiKeysModal = () => {
    setApiKeysModalOpen(false);
  };

  const revokeKey = async (record: any) => {
    await fetch(
      process.env.REACT_APP_API_URL + '/v1/key?key=' + record.key,
      { method: 'DELETE', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } }
    );
    await fetchApiKeys();
  };

  const showPaymentModal = () => {
    setPaymentModalOpen(true);
  };

  const cancelPaymentModal = () => {
    setPaymentModalOpen(false);
  };

  const translateCheckboxOnChange = () => {
    setTranslate((t) => !t);
  };

  const loadVideo = (file: any) => new Promise((resolve, reject) => {
    try {
      let video = document.createElement('video')
      video.preload = 'metadata'
      video.onloadedmetadata = function () {
        resolve(this)
      }
      video.onerror = function () {
        reject("Invalid video. Please select a video file.")
      }
      video.src = window.URL.createObjectURL(file)
    } catch (e) {
      reject(e)
    }
  });

  const convertFileToBlobAndDownload = async (file: any, name: any) => {
    const blob = await (await fetch(file)).blob();
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.style.display = 'none';
    a.href = url;
    a.download = name;
    document.body.appendChild(a);
    a.click();
    window.URL.revokeObjectURL(url);
  }

  const columns: ColumnsType<any> = [
    {
      title: 'Filename',
      dataIndex: 'original_name',
      key: 'original_name',
      onCell: () => {
        return {
          style: {
            whiteSpace: 'pre-wrap',
            maxWidth: 250,
          }
        }
      },
      render: text => <div style={{ textOverflow: 'ellipsis', overflow: 'hidden' }}>{text}</div>,
    },
      {
        title: 'Upload date',
        dataIndex: 'uploaded_at',
        key: 'uploaded_at',
        sorter: (a, b) => new Date(a.uploaded_at).valueOf() - new Date(b.uploaded_at).valueOf(),
          defaultSortOrder: 'descend',
      },
      {
        title: 'Translate',
        key: 'translate',
        render: (_, record) => {
          return record.filename.includes('translate') ? 'Yes' : 'No'
        },
      },
      {
        title: 'Cost (credits)',
        dataIndex: 'cost',
        key: 'cost',
      },
      {
        title: 'Status',
        dataIndex: 'status',
        key: 'status',
        render: (status) => {
          return <Tag>{status}</Tag>
        },
      },
      {
        title: 'Downloads',
        key: 'actions',
        render: (_, record) => (<>
          {record.status === 'Done' &&
          <div style={{ display: 'flex' }}>
            <Button type="link" icon={<DownloadOutlined />} style={{ marginLeft: '5px' }} onClick={() => convertFileToBlobAndDownload(record.txt, record.original_name + '.txt')} download>
              .txt
            </Button>
            <Button type="link" icon={<DownloadOutlined />} style={{ marginLeft: '5px' }} onClick={() => convertFileToBlobAndDownload(record.srt, record.original_name + '.srt')} download>
              .srt
            </Button>
            <Button type="link" icon={<DownloadOutlined />} style={{ marginLeft: '5px' }} onClick={() => convertFileToBlobAndDownload(record.vtt, record.original_name + '.vtt')} download>
              .vtt
            </Button>
          </div>
          }
        </>),
      },
  ];

  useInterval(async () => {
    for (const upload of uploads) {
      if (upload.status === 'In progress') {
        const transcriptionResp = await (await fetch(
          process.env.REACT_APP_API_URL + '/v1/transcription?' + new URLSearchParams({ filename: upload.filename }),
          { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } },
        )).json();
        if (transcriptionResp?.txt?.length) {
          const uploadResp = await (await fetch(
            process.env.REACT_APP_API_URL + '/v1/upload',
            { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } }
          )).json();
          setUploads(uploadResp.uploads.map((u: any) => {
            u.uploaded_at = u.uploaded_at.$date;
            u.key = u._id.$oid
            return u;
          }));
        }
      }
    }
  }, 10000);

  const logout = () => {
    localStorage.removeItem('access');
    navigate('/');
  };

  useEffect(() => {
    if (!localStorage.getItem('access')?.length)
      navigate('/');
    if (new Date(localStorage.getItem('expiry') as string) < new Date()) {
      localStorage.clear();
      navigate('/');
    }
  }, []);

  useEffect(() => {
    fetch(
      process.env.REACT_APP_API_URL + '/v1/upload',
      { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } }
    ).then((r) => r.json())
    .then((r) => {
      setUploads(r.uploads.map((u: any) => {
        u.uploaded_at = u.uploaded_at.$date;
        u.key = u._id.$oid
        return u;
      }));
    });
  }, [refetch]);

  useEffect(() => {
    fetch(
      process.env.REACT_APP_API_URL + '/v1/credits',
      { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } }
    ).then((r) => r.json())
    .then((r) => {
      setCredits(r.credits);
    });
  }, [refetch]);

  const uploadProps: UploadProps = {
    name: 'file',
    multiple: true,
    accept: '.3gp,.aiff,.avi,.flac,.flv,.m4a,.mkv,.mov,.mp3,.mp4,.ogg,.wav,.webm,.wma,.wmv',
    headers: {
      Authorization: 'Bearer ' + localStorage.getItem('access'),
    },
    showUploadList: {
      showRemoveIcon: false,
    },
    action: process.env.REACT_APP_API_URL + '/v1/upload',
    async beforeUpload(file) {
      const video: any = await loadVideo(file);
      if (Math.ceil(video.duration / 60) > credits) {
        message.error('Not enough credits');
        return false;
      }
    },
    data: () => {return {translate: translate, language: language}},
      async onChange(info) {
      const { status } = info.file;
      if (status !== 'uploading') {
      }
      if (status === 'done') {
        message.success(`${info.file.name} file uploaded successfully.`);

        await fetch(
          process.env.REACT_APP_API_URL + '/v1/transcription?' + new URLSearchParams({ filename: info.file.response.filename }),
          { method: 'GET', headers: { Authorization: 'Bearer ' + localStorage.getItem('access') } },
        );

        setRefetch(new Date());
      } else if (status === 'error') {
        message.error(`${info.file.name} file upload failed.`);
      }
    },
  };

  const apiMenu = (
    <Menu items={[
      {
        key: '1',
        label: (
          <Button onClick={() => window.location.replace('https://speechwave.ai/apidocs')}>Docs</Button>
        ),
      },
      {
        key: '2',
        label: (
          <Button onClick={openApiKeysModal}>Keys</Button>
        ),
      }
    ]} />
  );

  const apiKeysTableColumns: ColumnsType<any> = [
    {
      title: 'Key',
      dataIndex: 'key',
      key: 'key',
    },
    {
      title: 'Creation date',
      dataIndex: 'created_at',
      key: 'created_at',
      sorter: (a: any, b: any) => new Date(a.created_at).valueOf() - new Date(b.created_at).valueOf(),
        defaultSortOrder: 'descend',
    },
    {
      title: 'Actions',
      key: 'actions',
      render: (_: any, record: any) => (<>
        <Button type="primary" danger icon={<DeleteOutlined />} onClick={() => revokeKey(record)}>
          Revoke
        </Button>
      </>),
    },
  ];

  const creditHistoryTableColumns: ColumnsType<any> = [
    {
      title: 'Type',
      dataIndex: 'type',
      key: 'type',
      render: (value: any) => {
        return value === 'deduct' ? <><MinusOutlined style={{ color: 'red' }} /> Deduct</> : <><PlusOutlined style={{ color: 'green' }}/> Add</>
      }
    },
    {
      title: 'Date',
      dataIndex: 'date',
      key: 'date',
      sorter: (a: any, b: any) => new Date(a.date).valueOf() - new Date(b.date).valueOf(),
        defaultSortOrder: 'descend',
    },
    {
      title: 'Reason',
      dataIndex: 'reason',
      key: 'reason',
    },
    {
      title: 'Filename',
      dataIndex: 'filename',
      key: 'filename',
      onCell: () => {
        return {
          style: {
            whiteSpace: 'pre-wrap',
            maxWidth: 250,
          }
        }
      },
      render: text => <div style={{ textOverflow: 'ellipsis', overflow: 'hidden' }}>{text}</div>,
    },
    {
      title: 'Amount',
      dataIndex: 'amount',
      key: 'amount',
    },
  ];

  return (
    <div>
      <div style={{ margin: '0 auto', width: '1000px' }}>
        <img src={logo} style={{ display: 'inline-block', width: '150px', marginRight: '10px' }}/>
        <Tag color="geekblue" style={{ marginTop: '20px', cursor: 'pointer' }} onClick={openCreditHistoryModal}>Credits: {credits} minutes <CaretDownOutlined /></Tag>
        <Button type="primary" icon={<DollarOutlined />} onClick={showPaymentModal}>
          Buy credits
        </Button>
        <Button type="primary" danger icon={<LogoutOutlined />} style={{ marginLeft: '10px' }} onClick={logout}>
          Log out
        </Button>
        <Dropdown overlay={apiMenu} placement="bottomRight">
          <Button style={{ float: 'right', marginTop: '15px' }}>API</Button>
        </Dropdown>
        <Card style={{ width: '100%', marginTop: '10px', height: '50px', display: 'flex', flexDirection: 'column', justifyContent: 'center' }}>
          <span style={{ bottom: '8px', position: 'relative', marginRight: '10px' }}>Language:</span>
          <Select defaultValue="Auto-detect" style={{ width: '20%', position: 'relative', bottom: '8px' }} onChange={languageChanged} value={language}>
            <Select.Option value="Auto-detect">Auto-detect</Select.Option>
            {languages.map((l) => {
              return <Select.Option value={l}>{l}</Select.Option>
            })}
          </Select>
          <Checkbox onChange={translateCheckboxOnChange} checked={translate} style={{ marginTop: '20px', position: 'relative', bottom: '8px', marginLeft: '10px' }}>Translate to English</Checkbox>
          {language === 'Auto-detect' &&
          <span style={{ bottom: '8px', position: 'relative', marginLeft: '28px', fontSize: '11px', height: '30px' }}><WarningTwoTone twoToneColor='#eb2f96' style={{ marginRight: '10px' }} />If there's no speech within the first 30 seconds then you need to select the language manually.</span>
          }
        </Card>
        <Dragger {...uploadProps} style={{ marginTop: '5px', width: '100%', height: '100%' }}>
          <p className="ant-upload-drag-icon">
            <InboxOutlined />
          </p>
          <p className="ant-upload-text">Click or drag file to this area to upload</p>
          <p className="ant-upload-hint">
            Support for a single or bulk upload.
          </p>
        </Dragger>
        <Table columns={columns} dataSource={uploads} style={{ marginTop: '30px', width: '1000px' }}/>
      </div>
      <Modal
        open={paymentModalOpen}
        title="Buy credits"
        onCancel={cancelPaymentModal}
        footer={[<Button key="back" onClick={cancelPaymentModal}>Cancel</Button>]}
      >
        <span style={{ display: 'flex', marginBottom: '20px', width: '100%', alignItems: 'center' }}>
          <h4 style={{ width: '100%' }}>
            How many credits do you wish to purchase?
          </h4>
          <InputNumber defaultValue={1000} min={1} max={999999999999} disabled={clientSecret ? true : false} style={{ marginLeft: '10px', width: '65%' }} onChange={buyCreditAmountChange}></InputNumber>
          {clientSecret ? <Button type="primary" style={{ marginLeft: '5px' }} onClick={onEditClick} icon={<EditOutlined />}>Edit</Button> :
          <Button type="primary" style={{ marginLeft: '5px' }} onClick={onBuyClick} icon={<DollarOutlined />}>Buy</Button>
          }
        </span>
        <span style={{ display: 'flex' }}>
          <h5 style={{ marginBottom: '20px' }}>
            1 credit = 1 minute = 0.10 USD
          </h5>
          <h5 style={{ marginLeft: 'auto' }}>
            Total: ${(buyCreditAmount * 0.1).toFixed(2)}
          </h5>
        </span>
        {clientSecret && stripePromise && (
          <Elements stripe={stripePromise} options={{ clientSecret }}>
            <CheckoutForm />
          </Elements>
        )}
      </Modal>
      <Modal
        open={apiKeysModalOpen}
        title="API Keys"
        onCancel={cancelApiKeysModal}
        footer={[<Button key="back" onClick={cancelApiKeysModal}>Close</Button>]}
        width={1000}
      >
        <Button type="primary" icon={<PlusOutlined />} style={{ marginBottom: '10px' }} onClick={generateApiKey}>Generate new API key</Button>
        <Table columns={apiKeysTableColumns} dataSource={apiKeys} />
      </Modal>
      <Modal
        open={creditHistoryModalOpen}
        title="Credit History"
        onCancel={cancelCreditHistoryModal}
        footer={[<Button key="back" onClick={cancelCreditHistoryModal}>Close</Button>]}
        width={1000}
      >
        <CSVLink filename='speechwave-credit-history.csv' data={creditHistory.map((h: any) => { delete h._id; return h; })}>Download as CSV</CSVLink>
        <Table columns={creditHistoryTableColumns} dataSource={creditHistory} style={{ marginTop: '20px' }}/>
      </Modal>
      <Modal
        open={paymentSuccessModalOpen}
        onCancel={cancelPaymentSuccessModal}
        footer={[<Button key="back" onClick={cancelPaymentSuccessModal}>Close</Button>]}
        width={1000}
      >
        <CheckCircleTwoTone twoToneColor="#52c41a" style={{ fontSize: '24px', top: '4px', position: 'relative' }}/>&nbsp;&nbsp;&nbsp;Payment was successful! You will see your credit balance increased within a minute, if not then please refresh the page.
      </Modal>
    </div>
  );
}

export default Dashboard;
