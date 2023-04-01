import { Key, Suspense, useState } from 'react';
import { BlitzPage } from "@blitzjs/next"
import { Button, Card, Checkbox, Grid, Input, Modal, Row, Spacer, Table, Text } from '@nextui-org/react';
import { useCurrentUser } from 'src/users/hooks/useCurrentUser';
import { SignIn } from './login';
import { HiOutlineTranslate } from 'react-icons/hi';
import { BsChatText, BsMagic } from 'react-icons/bs';
import { FiFileText } from 'react-icons/fi';
import { MdNavigateNext } from 'react-icons/md';

const Dashboard = (props: any) => {
  const currentUser = useCurrentUser();

  const columns = [
    {
      key: "upload_name",
      label: "Upload Name",
    },
    {
      key: "length",
      label: "Length",
    },
    {
      key: "transcription",
      label: "Transcription",
    },
    {
      key: "translation",
      label: "Translation",
    },
    {
      key: 'enhancement',
      label: "Speech Enhancement",
    },
    {
      key: 'summarization',
      label: "Summarization",
    }
  ];

  const rows = [
    {
      key: "1",
      upload_name: "Hot secks in the bedroom on top of the bed.mp4",
      length: "42069",
    },
    {
      key: "2",
      upload_name: "Adele's_sister_screaming_for_mercy.mp3",
      length: "6931",
    },
  ];

  const getColumnLabel = (column: any) => {
    if (column.key === 'transcription') {
      return <div style={{ display: 'flex', gap: '4px' }}>
        <BsChatText style={{ fontSize: '16px' }}/> {column.label}
      </div>;
    } else if (column.key === 'translation') {
      return <div style={{ display: 'flex', gap: '4px' }}>
        <HiOutlineTranslate style={{ fontSize: '16px' }}/> {column.label}
      </div>;
    } else if (column.key === 'enhancement') {
      return <div style={{ display: 'flex', gap: '4px' }}>
        <BsMagic style={{ fontSize: '16px' }}/> {column.label}
      </div>;
    } else if (column.key === 'summarization') {
      return <div style={{ display: 'flex', gap: '4px' }}>
        <FiFileText style={{ fontSize: '16px' }}/> {column.label}
      </div>;
    } else {
      return column.label;
    }
  };

  const getRowValue = (item: any, columnKey: any) => {
    if (columnKey === 'transcription') {
      return <Button bordered color="gradient" auto style={{ width: '100%' }}>
        Transcribe
      </Button>;
    } else if (columnKey === 'translation') {
      return <Button bordered color="gradient" auto style={{ width: '100%' }}>
        Translate
      </Button>;
    } else if (columnKey === 'enhancement') {
      return <Button bordered color="gradient" auto style={{ width: '100%' }}>
        Enhance
      </Button>;
    } else if (columnKey === 'summarization') {
      return <Button bordered color="gradient" auto style={{ width: '100%' }}>
        Summarize
      </Button>;
    }
    else if (columnKey === 'length') return item[columnKey] + 's';
    else return item[columnKey];
  };

  const [selectedCount, setSelectedCount] = useState(0);

  const onSelectionChange = (selected: Set<Key> | string) => {
    if (typeof selected !== 'string') {
      setSelectedCount(selected.size);
    } else if (selected === 'all') {
      setSelectedCount(rows.length);
    }
  };

  const [visible, setVisible] = useState(false);
  const handler = () => setVisible(true);

  const closeHandler = () => {
    setVisible(false);
  };

  if (!currentUser) return <SignIn {...props} />;

  return (
    <>
      <Modal
        closeButton
        aria-labelledby="modal-title"
        open={visible}
        onClose={closeHandler}
      >
        <Modal.Header>
          <Text id="modal-title" size={18}>
            Welcome to
            <Text b size={18}>
              NextUI
            </Text>
          </Text>
        </Modal.Header>
        <Modal.Body>
          <Input
            clearable
            bordered
            fullWidth
            color="primary"
            size="lg"
            placeholder="Email"
          />
          <Input
            clearable
            bordered
            fullWidth
            color="primary"
            size="lg"
            placeholder="Password"
          />
          <Row justify="space-between">
            <Checkbox>
              <Text size={14}>Remember me</Text>
            </Checkbox>
            <Text size={14}>Forgot password?</Text>
          </Row>
        </Modal.Body>
        <Modal.Footer>
          <Button auto flat color="error" onPress={closeHandler}>
            Close
          </Button>
          <Button auto onPress={closeHandler}>
            Sign in
          </Button>
        </Modal.Footer>
      </Modal>
      <Grid.Container gap={2} justify="center">
        <Grid xs={12}>
          <div style={{ width: '100%' }}>
            {selectedCount > 0 &&
            <Card style={{ width: '100%', marginBottom: '10px', paddingLeft: '20px' }}>
              <Card.Body>
                <div style={{ display: 'flex', justifyContent: 'center', alignItems: 'baseline' }}>
                  <Text
                    h1
                    size={18}
                    css={{
                      textGradient: '45deg, $blue600 -20%, $pink600 50%',
                    }}
                    weight="bold"
                  >{selectedCount} upload{selectedCount > 1 && 's'} selected</Text>
                <Spacer x={1} />
                <Button color="gradient" style={{ fontSize: '16px', fontWeight: '800' }} onPress={handler}>
                  Proceed <MdNavigateNext size="24" />
                </Button>
              </div>
            </Card.Body>
          </Card>
        }
        <Table
          aria-label="Example dynamic collection table with color selection"
          color={'primary'}
          selectionMode="multiple"
          containerCss={{ height: 'auto', minWidth: '100%' }}
          onSelectionChange={onSelectionChange}
        >
          <Table.Header columns={columns}>
            {(column) => (
              <Table.Column key={column.key}>{getColumnLabel(column)}</Table.Column>
            )}
          </Table.Header>
          <Table.Body items={rows}>
            {(item) => (
              <Table.Row key={item.key}>
                {(columnKey) => <Table.Cell>{getRowValue(item, columnKey)}</Table.Cell>}
              </Table.Row>
            )}
          </Table.Body>
        </Table>
      </div>
    </Grid>
  </Grid.Container>
</>
);
};

const DashboardPage: BlitzPage = (props: any) => {
  return (
    <Suspense>
      <Dashboard {...props}/>
    </Suspense>
  );
}

export default DashboardPage;
